
#include "assembly_builder.h"

#include <vector>

using namespace llvm;
using namespace c1_recognizer::syntax_tree;

void assembly_builder::visit(assembly &node)
{
    ptr_list<global_def_syntax> children = node.global_defs;
    error_flag = false;
    for(int i = 0;i < children.size();i++){
        /** 在访问的过程中生成中间代码 **/
        in_global = true;
        children[i]->accept(*this);
    }
}

void assembly_builder::visit(func_def_syntax &node)
{
    in_global = false;
    if(functions.find(node.name) != functions.end()){
        //语义检查：函数重命名
        error_flag = true;
        err.error(node.line,node.pos,"函数重定义：" + node.name);
        return;
    }
    current_function = Function::Create(FunctionType::get(Type::getVoidTy(context), {}, false),
                                        GlobalValue::LinkageTypes::ExternalLinkage,
                                        node.name, module.get());
    /** 将新创建的函数加入函数名维护表 **/
    functions.emplace(node.name,current_function);
    /** 创建初始块开始代码生成 **/
    auto initBB = BasicBlock::Create(context,"InitBlock",current_function);
    builder.SetInsertPoint(initBB);
    node.body->accept(*this);
    builder.CreateRetVoid();
}

void assembly_builder::visit(cond_syntax &node)
{
    //条件语句的生成
    Value* LeftOpe;
    Value* RightOpe;

    constexpr_expected = false;
    node.lhs->accept(*this);
    LeftOpe = value_result;

    constexpr_expected = false;
    node.rhs->accept(*this);
    RightOpe = value_result;

    //在cond里面，遇到float和int比较，要把int转换成float吗    要转换
    if(LeftOpe->getType() == Type::getDoubleTy(context) && RightOpe->getType() != Type::getDoubleTy(context)){
        RightOpe = builder.CreateSIToFP(RightOpe,Type::getDoubleTy(context));
    }
    if(LeftOpe->getType() != Type::getDoubleTy(context) && RightOpe->getType() == Type::getDoubleTy(context)){
        LeftOpe = builder.CreateSIToFP(LeftOpe,Type::getDoubleTy(context));
    }
    /******************************************************************************************/
    //语义检查：浮点型表达式之间不能进行 == 或 != 关系运算
    if(node.op == relop::equal){
        if(LeftOpe->getType() == Type::getDoubleTy(context)){
            value_result = ConstantInt::get(Type::getInt32Ty(context),0);
            error_flag = true;
            err.error(node.line,node.pos,"浮点型表达式之间不能进行 == 或 != 关系运算");
            return;
        }
        value_result = builder.CreateICmpEQ(LeftOpe,RightOpe);
    }
    if(node.op == relop::non_equal){
        if(LeftOpe->getType() == Type::getDoubleTy(context)){
            value_result = ConstantInt::get(Type::getInt32Ty(context),0);
            error_flag = true;
            err.error(node.line,node.pos,"浮点型表达式之间不能进行 == 或 != 关系运算");
            return;
        }
        value_result = builder.CreateICmpNE(LeftOpe,RightOpe);
    }
    /****************************************************************************************/
    if(node.op == relop::greater){
        if(LeftOpe->getType() == Type::getDoubleTy(context)){
            value_result = builder.CreateFCmpOGT(LeftOpe,RightOpe);
        }
        else{
            value_result = builder.CreateICmpSGT(LeftOpe,RightOpe);
        }
    }
    if(node.op == relop::greater_equal){
        if(LeftOpe->getType() == Type::getDoubleTy(context)){
            value_result = builder.CreateFCmpOGE(LeftOpe,RightOpe);
        }
        else{
            value_result = builder.CreateICmpSGE(LeftOpe,RightOpe);
        }
    }
    if(node.op == relop::less){
        if(LeftOpe->getType() == Type::getDoubleTy(context)){
            value_result = builder.CreateFCmpOLT(LeftOpe,RightOpe);
        }
        else{
            value_result = builder.CreateICmpSLT(LeftOpe,RightOpe);
        }
    }
    if(node.op == relop::less_equal){
        if(LeftOpe->getType() == Type::getDoubleTy(context)){
            value_result = builder.CreateFCmpOLE(LeftOpe,RightOpe);
        }
        else{
            value_result = builder.CreateICmpSLE(LeftOpe,RightOpe);
        }
    }
}

void assembly_builder::visit(binop_expr_syntax &node)
{
    //双操作数表达式的生成
    if(constexpr_expected){
        bool is_float = false;

        int TempLeftInt,TempRightInt;
        double TempLeftFloat,TempRightFloat;

        node.lhs->accept(*this);
        if(is_result_int){
            TempLeftInt = int_const_result;
            TempLeftFloat = int_const_result;
        }
        else{
            TempLeftInt = float_const_result;
            TempLeftFloat = float_const_result;
            is_float = true;
        }

        node.rhs->accept(*this);
        if(is_result_int){
            TempRightInt = int_const_result;
            TempRightFloat = int_const_result;
        }
        else{
            TempRightInt = float_const_result;
            TempRightFloat = float_const_result;
            is_float = true;
        }

        if(is_float){
            is_result_int = false;
            switch(node.op){
                case binop::plus :
                    float_const_result = TempLeftFloat + TempRightFloat;
                    break;
                case binop::minus :
                    float_const_result = TempLeftFloat - TempRightFloat;
                    break;
                case binop::multiply :
                    float_const_result = TempLeftFloat * TempRightFloat;
                    break;
                //根据C++标准，浮点数除法、取模，除数可以是0，结果为NAN
                case binop::divide :
                    float_const_result = TempLeftFloat / TempRightFloat;
                    break;
                case binop::modulo :
                    float_const_result = fmod(TempLeftFloat, TempRightFloat);
                    break;
            }
        }
        else{
            is_result_int = true;
            switch(node.op){
                case binop::plus :
                    int_const_result = TempLeftInt + TempRightInt;
                    break;
                case binop::minus :
                    int_const_result = TempLeftInt - TempRightInt;
                    break;
                case binop::multiply :
                    int_const_result = TempLeftInt * TempRightInt;
                    break;
                case binop::divide :
                    //语义检查：整形除法除数为0
                    if(TempRightInt == 0){
                        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
                        int_const_result = 0;
                        error_flag = true;
                        err.error(node.line,node.pos,"整形除法除数为零");
                        return;
                    }
                    int_const_result = TempLeftInt / TempRightInt;
                    break;
                case binop::modulo :
                    if(TempRightInt == 0){
                        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
                        int_const_result = 0;
                        error_flag = true;
                        err.error(node.line,node.pos,"整形取模除数为零");
                        return;
                    }
                    int_const_result = TempLeftInt % TempRightInt;
                    break;
            }
        }
    }
    else{
        Value* TempLeft;
        Value* TempRight;
        node.lhs->accept(*this);
        TempLeft = value_result;
        node.rhs->accept(*this);
        TempRight = value_result;
        /***********************************************************************************/
        //进行一下类型统一
        if(TempLeft->getType() == Type::getDoubleTy(context) && TempRight->getType() != Type::getDoubleTy(context)){
            TempRight = builder.CreateSIToFP(TempRight,Type::getDoubleTy(context));
        }
        if(TempLeft->getType() != Type::getDoubleTy(context) && TempRight->getType() == Type::getDoubleTy(context)){
            TempLeft = builder.CreateSIToFP(TempLeft,Type::getDoubleTy(context));
        }
        /*********************************************************************************/
        if(TempLeft->getType() == Type::getDoubleTy(context)){
            switch(node.op){
                case binop::plus :
                    value_result = builder.CreateFAdd(TempLeft,TempRight);
                    break;
                case binop::minus :
                    value_result = builder.CreateFSub(TempLeft,TempRight);
                    break;
                case binop::multiply :
                    value_result = builder.CreateFMul(TempLeft,TempRight);
                    break;
                case binop::divide :
                    value_result = builder.CreateFDiv(TempLeft,TempRight);
                    break;
                case binop::modulo :
                    value_result = builder.CreateFRem(TempLeft,TempRight);
                    break;
            }
        }
        else{
            switch(node.op){
                case binop::plus :
                    value_result = builder.CreateAdd(TempLeft,TempRight);
                    break;
                case binop::minus :
                    value_result = builder.CreateSub(TempLeft,TempRight);
                    break;
                case binop::multiply :
                    value_result = builder.CreateMul(TempLeft,TempRight);
                    break;
                case binop::divide :
                    value_result = builder.CreateSDiv(TempLeft,TempRight);
                    break;
                case binop::modulo :
                    value_result = builder.CreateSRem(TempLeft,TempRight);
                    break;
            }
        }
    }
}

void assembly_builder::visit(unaryop_expr_syntax &node)
{
    //单操作数表达式的生成
    if(constexpr_expected){
        node.rhs->accept(*this);
        if(node.op == unaryop::minus){
            int_const_result = -int_const_result;
            float_const_result = -float_const_result;
        }
    }
    else{
        node.rhs->accept(*this);
        if(node.op == unaryop::minus){
            value_result = builder.CreateNeg(value_result);
        }
    }
}

void assembly_builder::visit(lval_syntax &node)
{
    //变量使用语句的生成
    //首先判断变量是否存在在环境中
    auto VariableInformation = lookup_variable(node.name);
    if(std::get<0>(VariableInformation) == nullptr){
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"未定义变量:" + node.name);
        return;
    }
    //因为变量并非常量表达式
    if(constexpr_expected){
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"变量并非常量表达式：  " + node.name);
        return;
    }
    //然后判断是作为左值使用还是作为右值使用
    if(node.array_index == nullptr){
        /**************************************************************/
        //语义检查：对数组元素未进行索引
        if(std::get<2>(lookup_variable(node.name)) == true){
            value_result = ConstantInt::get(Type::getInt32Ty(context),0);
            error_flag = true;
            err.error(node.line,node.pos,"对数组元素未进行索引" + node.name);
            return;
        }
        /**************************************************************/
        value_result = std::get<0>(lookup_variable(node.name));
        if(lval_as_rval){
            value_result = builder.CreateLoad(value_result);
        }
    }
    else{
        /**************************************************************/
        //语义检查：对非数组元素进行索引
        if(std::get<2>(lookup_variable(node.name)) == false){
            value_result = ConstantInt::get(Type::getInt32Ty(context),0);
            error_flag = true;
            err.error(node.line,node.pos,"对非数组元素进行索引" + node.name);
            return;
        }
        /**************************************************************/
        bool constexpr_expected_tmp = constexpr_expected;
        constexpr_expected = false;
        bool lval_as_rval_tmp = lval_as_rval;
        lval_as_rval = true;

        node.array_index->accept(*this);

        lval_as_rval = lval_as_rval_tmp;
        constexpr_expected = constexpr_expected_tmp;

        std::vector<Value*> ArrayIndex;
        /*************************************************************/
        //语义检查：非整形索引
        if(value_result->getType() != Type::getInt32Ty(context)){
            value_result = ConstantInt::get(Type::getInt32Ty(context),0);
            error_flag = true;
            err.error(node.line,node.pos,"非整形索引" + node.name);
            return;
        }
        /*************************************************************/
        ArrayIndex.push_back(ConstantInt::get(Type::getInt32Ty(context),0));
        ArrayIndex.push_back(value_result);
        Value* ArrayPtr = std::get<0>(lookup_variable(node.name));
        value_result = builder.CreateGEP(ArrayPtr,ArrayIndex);
        if(lval_as_rval){
            value_result = builder.CreateLoad(value_result);
        }
    }
}

void assembly_builder::visit(literal_syntax &node)
{
    //字面量的生成
    if(constexpr_expected){
        if(node.is_int){
            is_result_int = true;
            int_const_result = node.intConst;
        }
        else{
            is_result_int = false;
            float_const_result = node.floatConst;
        }
    }
    else{
        if(node.is_int){
            value_result = ConstantInt::get(Type::getInt32Ty(context),node.intConst);
        }
        else{
            value_result = ConstantFP::get(Type::getDoubleTy(context),node.floatConst);
        }
    }
}

void assembly_builder::visit(var_def_stmt_syntax &node)
{
    //定义语句的生成，即要产生一条allcoa指令
    //bool declare_variable(std::string name, llvm::Value *var_ptr, bool is_const, bool is_array, bool is_int)
    //先判断是否重复定义
    if(std::get<0>(lookup_variable(node.name)) != nullptr){
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"变量重复声明:" + node.name);
        return;
    }
    Value* VariPtr; //最后加入符号表的指针

    //是否是全局变量
    if(in_global){
        //全局变量
        //对于全局变量，无论变量为常量或可变量，其初始化表达式均要求是常量表达式
        constexpr_expected = true;
        if(node.array_length == nullptr){
            if(node.is_int){
                ConstantInt* init;
                if(node.initializers.size() == 0){
                    init = ConstantInt::get(Type::getInt32Ty(context),0);
                }
                else{
                    node.initializers[0]->accept(*this);
                    if(is_result_int == false){
                        int_const_result = float_const_result;
                    }
                    init = ConstantInt::get(Type::getInt32Ty(context),int_const_result);
                }
                VariPtr = new GlobalVariable(*module.get(),Type::getInt32Ty(context),node.is_constant,GlobalValue::LinkageTypes::ExternalLinkage,init,node.name);
            }
            else{
                //ConstantFP* init;
                Constant* init;
                if(node.initializers.size() == 0){
                    init = ConstantFP::get(Type::getDoubleTy(context),0);
                }
                else{
                    node.initializers[0]->accept(*this);
                    if(is_result_int == true){
                        float_const_result = int_const_result;
                    }
                    init = ConstantFP::get(Type::getDoubleTy(context),float_const_result);
                }
                VariPtr = new GlobalVariable(*module.get(),Type::getDoubleTy(context),node.is_constant,GlobalValue::LinkageTypes::ExternalLinkage,init,node.name);
            }
        }
        else{
            //ConstantArray* init;
            Constant* init;
            
            node.array_length->accept(*this);
            int ArrayLength = int_const_result;
            /***********************************************************************/
            //语义检查：越界初始化
            if(node.initializers.size() > ArrayLength){
                value_result = ConstantInt::get(Type::getInt32Ty(context),0);
                error_flag = true;
                err.error(node.line,node.pos,"越界初始化" + node.name);
                return;
            }
            //语义检查：声明数组长度不是正数
            if(ArrayLength <= 0){
                value_result = ConstantInt::get(Type::getInt32Ty(context),0);
                error_flag = true;
                err.error(node.line,node.pos,"数组长度应为正数：" + node.name);
                return;
            }
            /***********************************************************************/
            std::vector<Constant* > InitializerList;
            if(node.is_int){
                for(int i = 0;i < node.initializers.size();i++){
                    node.initializers[i]->accept(*this);
                    if(is_result_int == false){
                        int_const_result = float_const_result;
                    }
                    InitializerList.push_back(ConstantInt::get(Type::getInt32Ty(context),int_const_result));
                }
                for(int i = node.initializers.size() ;i < ArrayLength;i++){
                    InitializerList.push_back(ConstantInt::get(Type::getInt32Ty(context),0));
                }
            }
            else{
                for(int i = 0;i < node.initializers.size();i++){
                    node.initializers[i]->accept(*this);
                    if(is_result_int == true){
                        float_const_result = int_const_result;
                    }
                    InitializerList.push_back(ConstantFP::get(Type::getDoubleTy(context),float_const_result));
                }
                for(int i = node.initializers.size() ;i < ArrayLength;i++){
                    InitializerList.push_back(ConstantFP::get(Type::getDoubleTy(context),0));
                }
            }
            /****************************************************************************************************/
            if(node.is_int){
                init = ConstantArray::get(ArrayType::get(Type::getInt32Ty(context),ArrayLength),InitializerList);
                //VariPtr = new GlobalVariable(*module.get(),Type::getInt32Ty(context),node.is_constant,GlobalValue::LinkageTypes::ExternalLinkage,init,node.name);
                VariPtr = new GlobalVariable(*module.get(),ArrayType::get(Type::getInt32Ty(context),ArrayLength),node.is_constant,GlobalValue::LinkageTypes::ExternalLinkage,init,node.name);
            }
            else{
                init = ConstantArray::get(ArrayType::get(Type::getDoubleTy(context),ArrayLength),InitializerList);
                //VariPtr = new GlobalVariable(*module.get(),Type::getDoubleTy(context),node.is_constant,GlobalValue::LinkageTypes::ExternalLinkage,init,node.name);
                VariPtr = new GlobalVariable(*module.get(),ArrayType::get(Type::getDoubleTy(context),ArrayLength),node.is_constant,GlobalValue::LinkageTypes::ExternalLinkage,init,node.name);
            }
        }
    }
    else{
        //局部变量
        //对于局部变量，无论变量为常量或可变量，其初始化表达式均不要求是常量表达式。
        constexpr_expected = false;
        if(node.array_length == nullptr){
            if(node.is_int){
                VariPtr = builder.CreateAlloca(Type::getInt32Ty(context),nullptr,node.name);
            }
            else{
                VariPtr = builder.CreateAlloca(Type::getDoubleTy(context),nullptr,node.name);
            }
            if(node.initializers.size() != 0){
                node.initializers[0]->accept(*this);
                /************************************************************************************************/
                if(node.is_int == true && value_result->getType() == Type::getDoubleTy(context)){
                    value_result = builder.CreateFPToSI(value_result,Type::getInt32Ty(context));
                }
                if(node.is_int == false && value_result->getType() == Type::getInt32Ty(context)){
                    value_result = builder.CreateSIToFP(value_result,Type::getDoubleTy(context));
                }
                /************************************************************************************************/
                builder.CreateStore(value_result,VariPtr);
            }
        }
        else{
            bool lval_as_rval_cache = lval_as_rval;
            bool constexpr_expected_cache = constexpr_expected;

            lval_as_rval = true;
            constexpr_expected = true; 

            node.array_length->accept(*this);

            lval_as_rval = lval_as_rval_cache;
            constexpr_expected = constexpr_expected_cache;
            /*****************************************************************************/
            //语义检查：越界初始化
            if(int_const_result < node.initializers.size()){
                value_result = ConstantInt::get(Type::getInt32Ty(context),0);
                error_flag = true;
                err.error(node.line,node.pos,"越界初始化：" + node.name);
                return;
            }
            //语义检查：声明数组长度不是正数
            if(int_const_result <= 0){
                value_result = ConstantInt::get(Type::getInt32Ty(context),0);
                error_flag = true;
                err.error(node.line,node.pos,"数组长度应为正数：" + node.name);
                return;
            }
            /******************************************************************************/
            if(node.is_int){
                VariPtr = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context),int_const_result),nullptr,node.name);
            }
            else{
                VariPtr = builder.CreateAlloca(ArrayType::get(Type::getDoubleTy(context),int_const_result),nullptr,node.name);
            }
            for(int i = 0;i < node.initializers.size();i++){
                node.initializers[i]->accept(*this);

                std::vector<Value*> ArrayIndex;
                ArrayIndex.push_back(ConstantInt::get(Type::getInt32Ty(context),0));
                ArrayIndex.push_back(ConstantInt::get(Type::getInt32Ty(context),i));
                /************************************************************************************************/
                if(node.is_int == true && value_result->getType() == Type::getDoubleTy(context)){
                    value_result = builder.CreateFPToSI(value_result,Type::getInt32Ty(context));
                }
                if(node.is_int == false && value_result->getType() == Type::getInt32Ty(context)){
                    value_result = builder.CreateSIToFP(value_result,Type::getDoubleTy(context));
                }
                /************************************************************************************************/
                Value* indexptr = builder.CreateGEP(VariPtr,ArrayIndex);
                builder.CreateStore(value_result,indexptr);
            }
        }
    }
    declare_variable(node.name,VariPtr,node.is_constant,node.array_length != nullptr,node.is_int);
}

void assembly_builder::visit(assign_stmt_syntax &node)
{
    //赋值语句的生成，即要产生一条store指令
    //这个点上target出错的情况比较多：
    if(std::get<0>(lookup_variable(node.target->name)) == nullptr){   //变量未声明
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"变量未声明:" + node.target->name );
        return;
    }
    //语义检查：常量赋值
    if(std::get<1>(lookup_variable(node.target->name)) == true){   //常量赋值
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"常量赋值" + node.target->name);
        return;
    }

    if(std::get<2>(lookup_variable(node.target->name)) == false && node.target->array_index != nullptr){   //对一般变量使用索引
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"违规使用变量名" + node.target->name);
        return;
    }
    if(std::get<2>(lookup_variable(node.target->name)) == true && node.target->array_index == nullptr){   //对数组元素不使用索引
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"违规使用数组名" + node.target->name);
        return;
    }
    //先获取target的地址
    lval_as_rval = false;
    node.target->accept(*this);
    Value* Target = value_result;
    //在获取value的值
    lval_as_rval = true;
    node.value->accept(*this);
    Value* ValueR = value_result;
    if( (Target->getType() == Type::getInt32Ty(context)     && ValueR->getType() != Type::getInt32Ty(context)) ||
        (Target->getType() == Type::getDoublePtrTy(context) && ValueR->getType() != Type::getDoubleTy(context)) ){
        if(Target->getType() == Type::getInt32PtrTy(context)){
            ValueR = builder.CreateFPToSI(ValueR,Type::getInt32Ty(context));
        }
        else{
            ValueR = builder.CreateSIToFP(ValueR,Type::getDoubleTy(context));
        }
    }
    builder.CreateStore(ValueR,Target);
}

void assembly_builder::visit(func_call_stmt_syntax &node)
{
    //函数调用语句的生成
    if(functions.find(node.name) == functions.end()){
        //函数未声明
        value_result = ConstantInt::get(Type::getInt32Ty(context),0);
        error_flag = true;
        err.error(node.line,node.pos,"函数未声明：" + node.name);
        return;
    }
    builder.CreateCall(functions[node.name]);
}

void assembly_builder::visit(block_syntax &node)
{
    //语句块的生成
    enter_scope();  //局部作用域
    ptr_list<stmt_syntax> BlockBody = node.body;
    for(int i = 0;i < BlockBody.size();i++){
        BlockBody[i]->accept(*this);
    }
    exit_scope();
}

//别忘了一定有一个 BB 块用作未来的代码生成，即这一控制流结构结束后的语句的 IR 插入点
void assembly_builder::visit(if_stmt_syntax &node)
{
    //if控制流
    auto if_cond_bb =    BasicBlock::Create(context,"if_cond_bb",current_function);
    //先创建着，有可能用不到
    auto else_block_bb = BasicBlock::Create(context,"else_block_bb",current_function);
    auto then_block_bb = BasicBlock::Create(context,"then_block_bb",current_function);
    auto exit_bb =       BasicBlock::Create(context,"exit_bb",current_function);
    //bb块有自动加编号避免冲突的功能，这里不再处理
    builder.CreateBr(if_cond_bb);
    builder.SetInsertPoint(if_cond_bb);
    node.pred->accept(*this);
    builder.CreateCondBr(value_result,then_block_bb,else_block_bb);

    builder.SetInsertPoint(then_block_bb);
    node.then_body->accept(*this);
    builder.CreateBr(exit_bb);

    builder.SetInsertPoint(else_block_bb);
    if(node.else_body){
        node.else_body->accept(*this);   
    }
    builder.CreateBr(exit_bb);

    builder.SetInsertPoint(exit_bb);
}

void assembly_builder::visit(while_stmt_syntax &node)
{
    //while控制流
    auto while_cond_bb = BasicBlock::Create(context,"while_cond_bb",current_function);
    auto while_body_bb = BasicBlock::Create(context,"while_body_bb",current_function);
    auto while_exit_bb = BasicBlock::Create(context,"while_exit_bb",current_function);

    builder.CreateBr(while_cond_bb);
    builder.SetInsertPoint(while_cond_bb);
    node.pred->accept(*this);
    builder.CreateCondBr(value_result,while_body_bb,while_exit_bb);

    builder.SetInsertPoint(while_body_bb);
    node.body->accept(*this);
    builder.CreateBr(while_cond_bb);

    builder.SetInsertPoint(while_exit_bb);
}

void assembly_builder::visit(empty_stmt_syntax &node)
{
    return;
}
