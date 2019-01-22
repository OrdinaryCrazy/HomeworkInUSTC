
#include "syntax_tree_builder.h"
#include <memory>

using namespace c1_recognizer;
using namespace c1_recognizer::syntax_tree;

syntax_tree_builder::syntax_tree_builder(error_reporter &_err) : err(_err) {}

antlrcpp::Any syntax_tree_builder::visitCompilationUnit(C1Parser::CompilationUnitContext *ctx)
{
    //编译单位
    //返回assembly型节点
    auto result = new assembly;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    auto Children = ctx->children;
    for(int i = 0;i < Children.size();i++){
        if(antlrcpp::is<C1Parser::DeclContext *>(Children[i])){
            std::vector<var_def_stmt_syntax *> declvec = visit(Children[i]);
            for(int j = 0;j < declvec.size();j++){
                result->global_defs.emplace_back(declvec[j]);
            }
        }
        if(antlrcpp::is<C1Parser::FuncdefContext *>(Children[i])){
            result->global_defs.emplace_back(visit(Children[i]).as<func_def_syntax *>());
        }
    }
    /**
    auto decls = ctx->decl();
    auto funcdefs = ctx->funcdef();
    if(decls.size() > 0){
        for(int i = 0;i < decls.size();i++){
            std::vector<var_def_stmt_syntax *> declvec = visit(ctx->decl(i));
            for(int j = 0;j < declvec.size();j++){
                result->global_defs.emplace_back(declvec[j]);
            }
        }
    }
    if(funcdefs.size() > 0){
        for(int i = 0;i < funcdefs.size();i++){
            result->global_defs.emplace_back(visit(ctx->funcdef(i)).as<func_def_syntax *>());
        }
    }
    **/
    return static_cast<assembly *>(result);
}

antlrcpp::Any syntax_tree_builder::visitDecl(C1Parser::DeclContext *ctx)
{
    //声明
    //返回var_def_stmt_syntax型节点的向量
    if(auto vardecls = ctx->constdecl()){
        return visit(vardecls);
    }
    if(auto constdecls = ctx->vardecl()){
        return visit(constdecls);
    }
}

antlrcpp::Any syntax_tree_builder::visitConstdecl(C1Parser::ConstdeclContext *ctx)
{
    //常量声明
    //返回var_def_stmt_syntax型节点的向量
    std::vector<var_def_stmt_syntax *> result;
    auto constdefs = ctx->constdef();
    if(ctx->Int()){
        for(int i = 0;i < constdefs.size();i++){
            auto ConstdefItem = visit(ctx->constdef(i)).as<var_def_stmt_syntax *>();
            ConstdefItem->is_int = true;
            result.emplace_back(ConstdefItem);
        }
    }
    if(ctx->Float()){
        for(int i = 0;i < constdefs.size();i++){
            auto ConstdefItem = visit(ctx->constdef(i)).as<var_def_stmt_syntax *>();
            ConstdefItem->is_int = false;
            result.emplace_back(ConstdefItem);
        }
    }
    return result;
}

antlrcpp::Any syntax_tree_builder::visitConstdef(C1Parser::ConstdefContext *ctx)
{
    //常量定义
    //返回var_def_stmt_syntax型节点
    auto result = new var_def_stmt_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->is_constant = true;
    result->name = ctx->Identifier()->getSymbol()->getText();
    if(ctx->LeftBracket() && ctx->RightBracket()){
        auto expressions = ctx->exp();
        auto commas = ctx->Comma();
        if(commas.size() == expressions.size() - 1){
            auto length = new literal_syntax;
            length->line = ctx->LeftBracket()->getSymbol()->getLine();
            length->pos = ctx->LeftBracket()->getSymbol()->getCharPositionInLine() + 1;
            length->is_int = true;
            length->intConst = expressions.size();
            result->array_length.reset( static_cast<expr_syntax *>(length) );
            for(int i = 0;i < expressions.size();i++){
                result->initializers.emplace_back( visit(ctx->exp(i)).as<expr_syntax *>() );
            }
        }
        if(commas.size() == expressions.size() - 2){
            result->array_length.reset( visit(ctx->exp(0)).as<expr_syntax *>() );
            for(int i = 1;i < expressions.size();i++){
                result->initializers.emplace_back( visit(ctx->exp(i)).as<expr_syntax *>() );
            }
        }
    }
    else{
        result->initializers.emplace_back( visit(ctx->exp(0)).as<expr_syntax *>() );
    }
    return static_cast<var_def_stmt_syntax *>(result);
}

antlrcpp::Any syntax_tree_builder::visitVardecl(C1Parser::VardeclContext *ctx)
{
    //变量声明
    //返回var_def_stmt_syntax型节点的向量
    std::vector<var_def_stmt_syntax *> result;
    auto vardefs = ctx->vardef();
    if(ctx->Int()){
        for(int i = 0;i < vardefs.size();i++){
            auto VardefItem = visit(ctx->vardef(i)).as<var_def_stmt_syntax *>();
            VardefItem->is_int = true;
            result.emplace_back(VardefItem);
        }
    }
    if(ctx->Float()){
        for(int i = 0;i < vardefs.size();i++){
            auto VardefItem = visit(ctx->vardef(i)).as<var_def_stmt_syntax *>();
            VardefItem->is_int = false;
            result.emplace_back(VardefItem);
        }
    }
    return result;
}

antlrcpp::Any syntax_tree_builder::visitVardef(C1Parser::VardefContext *ctx)
{
    //变量定义
    //返回var_def_stmt_syntax型节点
    auto result = new var_def_stmt_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->is_constant = false;
    if(ctx->Assign()){
        if(ctx->LeftBracket() && ctx->RightBracket()){
            result->name = ctx->Identifier()->getSymbol()->getText();
            auto expressions = ctx->exp();
            auto commas = ctx->Comma();
            if(commas.size() == expressions.size() - 1){
                auto length = new literal_syntax;
                length->line = ctx->LeftBracket()->getSymbol()->getLine();
                length->pos = ctx->LeftBracket()->getSymbol()->getCharPositionInLine() + 1;
                length->is_int = true;
                length->intConst = expressions.size();
                result->array_length.reset( static_cast<expr_syntax *>(length) );
                for(int i = 0;i < expressions.size();i++){
                    result->initializers.emplace_back( visit(ctx->exp(i)).as<expr_syntax *>() );
                }
            }
            if(commas.size() == expressions.size() - 2){
                result->array_length.reset( visit(ctx->exp(0)).as<expr_syntax *>() );
                for(int i = 1;i < expressions.size();i++){
                    result->initializers.emplace_back( visit(ctx->exp(i)).as<expr_syntax *>() );
                }
            }
        }
        else{
            result->name = ctx->Identifier()->getSymbol()->getText();
            result->initializers.emplace_back( visit(ctx->exp(0)).as<expr_syntax *>() );
            //result->initializers.emplace_back(static_cast<expr_syntax *>(visit(ctx->exp(0)) ));
        }
    }
    else{
        if(ctx->LeftBracket() && ctx->RightBracket()){
            result->name = ctx->Identifier()->getSymbol()->getText();
            //result->initializers.emplace_back( visit(ctx->exp(0)).as<expr_syntax *>() );
            result->array_length.reset( visit(ctx->exp(0)).as<expr_syntax *>() );
        }
        else{
            result->name = ctx->Identifier()->getSymbol()->getText();
        }
    }
    return static_cast<var_def_stmt_syntax *>(result);
}

antlrcpp::Any syntax_tree_builder::visitFuncdef(C1Parser::FuncdefContext *ctx)
{
    //函数定义
    //返回func_def_syntax型节点
    auto result = new func_def_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->name = ctx->Identifier()->getSymbol()->getText();
    result->body.reset(visit(ctx->block()).as<block_syntax *>());
    return static_cast<func_def_syntax *>(result);
}

antlrcpp::Any syntax_tree_builder::visitBlock(C1Parser::BlockContext *ctx)
{
    //块语句
    //返回block_syntax型节点
    auto result = new block_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    auto Children = ctx->children;

    for(int i = 0;i < Children.size();i++){
        if(antlrcpp::is<C1Parser::DeclContext *>(Children[i])){
            std::vector<var_def_stmt_syntax *> declvec = visit(Children[i]);
            for(int j = 0;j < declvec.size();j++){
                result->body.emplace_back(declvec[j]);
            }
        }
        else{
            if(antlrcpp::is<C1Parser::StmtContext *>(Children[i])){
                result->body.emplace_back(visit(Children[i]).as<stmt_syntax *>());
            }
        }
    }
    /**
    auto stmts = ctx->stmt();
    if(stmts.size() > 0){
        for(int i = 0;i < stmts.size();i++){
            result->body.emplace_back( visit(ctx->stmt(i)).as<stmt_syntax *>() );
        }
    }
    **/
    return static_cast<block_syntax *>(result);
}

antlrcpp::Any syntax_tree_builder::visitStmt(C1Parser::StmtContext *ctx)
{
    //语句
    //返回stmt_syntax型节点
    //stmt_syntax型节点有诸多子节点类型，故而没有自己的数据域
    if(ctx->Assign() && ctx->SemiColon())
    {   //赋值语句型节点
        auto result = new assign_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->target.reset(visit(ctx->lval()).as<lval_syntax *>());
        result->value.reset(visit(ctx->exp()).as<expr_syntax *>());
        return static_cast<stmt_syntax *>(result);
    }
    if(ctx->Identifier() && ctx->LeftParen() && ctx->RightParen() && ctx->SemiColon())
    {   //函数调用语句型节点
        auto result = new func_call_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->name = ctx->Identifier()->getSymbol()->getText();
        return static_cast<stmt_syntax *>(result);
    }
    if(ctx->block())
    {   //块语句型节点
        //auto result = new block_syntax;
        //result->line = ctx->getStart()->getLine();
        //result->pos = ctx->getStart()->getCharPositionInLine();
        //这个点上有点问题
        //result->body.push_back(visit(ctx->block()).as<stmt_syntax *>());
        //return static_cast<stmt_syntax *>(result);
        //return visit(ctx->block()).as<stmt_syntax *>();
        return static_cast<stmt_syntax *>(visit(ctx->block()).as<block_syntax *>());
    }
    if(ctx->If() && ctx->LeftParen() && ctx->RightParen())
    {   //if语句型节点
        auto result = new if_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->pred.reset(visit(ctx->cond()).as<cond_syntax *>());
        result->then_body.reset(visit(ctx->stmt(0)).as<stmt_syntax *>());
        if(ctx->Else()){
            result->else_body.reset(visit(ctx->stmt(1)).as<stmt_syntax *>());
        }
        else{
            result->else_body.reset(static_cast<stmt_syntax *>(nullptr));
        }
        return static_cast<stmt_syntax *>(result);
    }
    if(ctx->While() && ctx->LeftParen() && ctx->RightParen())
    {   //while语句型节点
        auto result = new while_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        result->pred.reset(visit(ctx->cond()).as<cond_syntax *>());
        result->body.reset(visit(ctx->stmt(0)).as<stmt_syntax *>());
        return static_cast<stmt_syntax *>(result);
    }
    if(ctx->SemiColon())
    {   //空语句型节点，不需要多加其他信息
        auto result = new empty_stmt_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        return static_cast<stmt_syntax *>(result);
    }
}

antlrcpp::Any syntax_tree_builder::visitLval(C1Parser::LvalContext *ctx)
{
    //字面量
    //返回lval_syntax型节点
    auto result = new lval_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    
    result->name = ctx->Identifier()->getSymbol()->getText();
    //std::cout<< result->name <<std::endl;
    if(ctx->LeftBracket() && ctx->LeftBracket()){
        result->array_index.reset(visit(ctx->exp()).as<expr_syntax *>());
    }
    else{
        result->array_index.reset(static_cast<expr_syntax *>(nullptr));
    }
    return static_cast<lval_syntax *>(result);
    //return static_cast<expr_syntax *>(result);
}

antlrcpp::Any syntax_tree_builder::visitCond(C1Parser::CondContext *ctx)
{
    //条件语句
    //返回条件语句节点
    auto conditions = ctx->exp();
    auto result = new cond_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->lhs.reset(visit(conditions[0]).as<expr_syntax *>());
    if(ctx->relop()->Equal())
        result->op = relop::equal;
    if(ctx->relop()->NonEqual())
        result->op = relop::non_equal;
    if(ctx->relop()->Less())
        result->op = relop::less;
    if(ctx->relop()->Greater())
        result->op = relop::greater;
    if(ctx->relop()->LessEqual())
        result->op = relop::less_equal;
    if(ctx->relop()->GreaterEqual())
        result->op = relop::greater_equal;
    result->rhs.reset(visit(conditions[1]).as<expr_syntax *>());
    return static_cast<cond_syntax *>(result);
}

// Returns antlrcpp::Any, which is constructable from any type.
// However, you should be sure you use the same type for packing and depacking the `Any` object.
// Or a std::bad_cast exception will rise.
// This function always returns an `Any` object containing a `expr_syntax *`.
antlrcpp::Any syntax_tree_builder::visitExp(C1Parser::ExpContext *ctx)
{
    // Get all sub-contexts of type `exp`.
    auto expressions = ctx->exp();
    // Two sub-expressions presented: this indicates it's a expression of binary operator, aka `binop`.
    if (expressions.size() == 2)
    {
        auto result = new binop_expr_syntax;    //双操作符节点
        // Set line and pos.
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();
        // visit(some context) is equivalent to calling corresponding visit method; dispatching is done automatically
        // by ANTLR4 runtime. For this case, it's equivalent to visitExp(expressions[0]).
        // Use reset to set a new pointer to a std::shared_ptr object. DO NOT use assignment; it won't work.
        // Use `.as<Type>()' to get value from antlrcpp::Any object; notice that this Type must match the type used in
        // constructing the Any object, which is constructed from (usually pointer to some derived class of
        // syntax_node, in this case) returning value of the visit call.
        result->lhs.reset(visit(expressions[0]).as<expr_syntax *>());
        // Check if each token exists.
        // Returnd value of the calling will be nullptr (aka NULL in C) if it isn't there; otherwise non-null pointer.
        if (ctx->Plus())    //这些都是对终结符的处理
            result->op = binop::plus;
        if (ctx->Minus())
            result->op = binop::minus;
        if (ctx->Multiply())
            result->op = binop::multiply;
        if (ctx->Divide())
            result->op = binop::divide;
        if (ctx->Modulo())
            result->op = binop::modulo;
        result->rhs.reset(visit(expressions[1]).as<expr_syntax *>());
        return static_cast<expr_syntax *>(result);  //类型转换
    }
    // Otherwise, if `+` or `-` presented, it'll be a `unaryop_expr_syntax`.
    if (ctx->Plus() || ctx->Minus())
    {
        auto result = new unaryop_expr_syntax;
        result->line = ctx->getStart()->getLine();
        result->pos = ctx->getStart()->getCharPositionInLine();

        if (ctx->Plus())
            result->op = unaryop::plus;
        if (ctx->Minus())
            result->op = unaryop::minus;
        result->rhs.reset(visit(expressions[0]).as<expr_syntax *>());
        return static_cast<expr_syntax *>(result);
    }
    // In the case that `(` exists as a child, this is an expression like `'(' expressions[0] ')'`.
    if (ctx->LeftParen())
        return visit(expressions[0]); // Any already holds expr_syntax* here, no need for dispatch and re-patch with casting.
    
    // If `number` exists as a child, we can say it's a literal integer expression.
    if (auto number = ctx->number())
        return visit(number);

    if (auto lval = ctx->lval())
        return static_cast<expr_syntax *>(visit(lval).as<lval_syntax *>());
        //return visit(lval);
}

antlrcpp::Any syntax_tree_builder::visitNumber(C1Parser::NumberContext *ctx)
{
    auto result = new literal_syntax;
    if (auto intConst = ctx->IntConst())
    {
        result->is_int = true;
        result->line = intConst->getSymbol()->getLine();
        result->pos = intConst->getSymbol()->getCharPositionInLine();
        auto text = intConst->getSymbol()->getText();
        /****************************************************************************/
        if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X'))                // Hexadecimal
        /****************************************************************************/
            result->intConst = std::stoi(text, nullptr, 16); // std::stoi will eat '0x'
        /* you need to add other situations here */
        /****************************************************************************/
        else                                               // Decimal
            result->intConst = std::stoi(text, nullptr, 10);
        /****************************************************************************/
        return static_cast<expr_syntax *>(result);
    }
    // else FloatConst
    else
    {
        /****************************************************************************/
        auto floatConst = ctx->FloatConst();
        result->is_int = false;
        result->line = floatConst->getSymbol()->getLine();
        result->pos = floatConst->getSymbol()->getCharPositionInLine();
        auto text = floatConst->getSymbol()->getText();
        /**
        if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X'))
            result->floatConst = std::stod(text, nullptr, 16);
        else
            result->floatConst = std::stod(text, nullptr, 10);
        **/
        result->floatConst = std::stod(text, nullptr);
        /****************************************************************************/
        return static_cast<expr_syntax *>(result);
    }
}

ptr<syntax_tree_node> syntax_tree_builder::operator()(antlr4::tree::ParseTree *ctx)
{
    auto result = visit(ctx);
    /****************************************************************************/
    /*
    //./build/externals/antlr4cpp/include/antlr4-runtime/tree/AbstractParseTreeVisitor.h
    virtual antlrcpp::Any visit(ParseTree *tree) override {
      return tree->accept(this);
    }
    */
    /****************************************************************************/
    if (result.is<syntax_tree_node *>())
        return ptr<syntax_tree_node>(result.as<syntax_tree_node *>());

    if (result.is<assembly *>())
        return ptr<syntax_tree_node>(result.as<assembly *>());

    if (result.is<global_def_syntax *>())
        return ptr<syntax_tree_node>(result.as<global_def_syntax *>());

    if (result.is<func_def_syntax *>())
        return ptr<syntax_tree_node>(result.as<func_def_syntax *>());

    if (result.is<cond_syntax *>())
        return ptr<syntax_tree_node>(result.as<cond_syntax *>());

    if (result.is<expr_syntax *>())
        return ptr<syntax_tree_node>(result.as<expr_syntax *>());

    if (result.is<binop_expr_syntax *>())
        return ptr<syntax_tree_node>(result.as<binop_expr_syntax *>());

    if (result.is<unaryop_expr_syntax *>())
        return ptr<syntax_tree_node>(result.as<unaryop_expr_syntax *>());

    if (result.is<lval_syntax *>())
        return ptr<syntax_tree_node>(result.as<lval_syntax *>());

    if (result.is<literal_syntax *>())
        return ptr<syntax_tree_node>(result.as<literal_syntax *>());

    if (result.is<stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<stmt_syntax *>());

    if (result.is<var_def_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<var_def_stmt_syntax *>());

    if (result.is<assign_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<assign_stmt_syntax *>());

    if (result.is<func_call_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<func_call_stmt_syntax *>());

    if (result.is<block_syntax *>())
        return ptr<syntax_tree_node>(result.as<block_syntax *>());

    if (result.is<if_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<if_stmt_syntax *>());

    if (result.is<while_stmt_syntax *>())
        return ptr<syntax_tree_node>(result.as<while_stmt_syntax *>());

    return nullptr;
}
