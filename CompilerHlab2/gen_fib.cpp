#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <memory>
#include <vector>

using namespace llvm;

int main(){
    LLVMContext context;
    IRBuilder<> builder(context);

    auto module = new Module("gen_fib",context);
    std::vector<Type*> ParameterForFib(1,Type::getInt32Ty(context));
    auto fib_func = Function::Create(FunctionType::get(
                                        Type::getInt32Ty(context),
                                        ParameterForFib,
                                        false),
                                    GlobalValue::LinkageTypes::ExternalLinkage,
                                    "fib",
                                    module);
    auto main_func = Function::Create(FunctionType::get(
                                        Type::getInt32Ty(context),
                                        std::vector<Type *>(),
                                        false),
                                    GlobalValue::LinkageTypes::ExternalLinkage,
                                    "main",
                                    module);

    auto main_init_bb               = BasicBlock::Create(context,"",main_func);
    auto main_loop_condition_bb     = BasicBlock::Create(context,"",main_func);
    auto main_loop_body_bb          = BasicBlock::Create(context,"",main_func);
    auto main_loop_iteration_bb     = BasicBlock::Create(context,"",main_func);
    auto main_exit_bb               = BasicBlock::Create(context,"",main_func);
    
    auto fib_init_condition_1_bb    = BasicBlock::Create(context,"",fib_func);
    auto fib_then_body_1_bb         = BasicBlock::Create(context,"",fib_func);
    auto fib_condition_2_bb         = BasicBlock::Create(context,"",fib_func);
    auto fib_then_body_2_bb         = BasicBlock::Create(context,"",fib_func);
    auto fib_else_body_2_bb         = BasicBlock::Create(context,"",fib_func);
    auto fib_exit_bb                = BasicBlock::Create(context,"",fib_func);

    builder.SetInsertPoint(main_init_bb);
    //AllocaInst* main_return_value = builder.CreateAlloca(Type::getInt32Ty(context));
    //AllocaInst* main_conut_value = builder.CreateAlloca(Type::getInt32Ty(context));
    AllocaInst* main_return_value = builder.CreateAlloca(Type::getInt32Ty(context));
    main_return_value->setAlignment(4);
    AllocaInst* main_count_value = builder.CreateAlloca(Type::getInt32Ty(context));
    main_count_value->setAlignment(4);
    StoreInst* just_for_align_9 = builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context),0,false),main_return_value);
    just_for_align_9->setAlignment(4);
    StoreInst* just_for_align_8 = builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context),1,false),main_count_value);
    just_for_align_8->setAlignment(4);
    builder.CreateBr(main_loop_condition_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(main_loop_condition_bb);
    LoadInst* Lhs = builder.CreateLoad(main_count_value);
    Lhs->setAlignment(4);
    Value* Cond = builder.CreateICmpSLT(Lhs,ConstantInt::get(Type::getInt32Ty(context),8,false));
    builder.CreateCondBr(Cond,main_loop_body_bb,main_exit_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(main_loop_body_bb);
    LoadInst* Paratofib = builder.CreateLoad(main_count_value);
    Paratofib->setAlignment(4);
    std::vector<Value*> Paratofibs;
    Paratofibs.push_back(Paratofib);
    Value* return_from_fib = builder.CreateCall(fib_func,Paratofibs);
    LoadInst* sum_tmp = builder.CreateLoad(main_return_value);
    sum_tmp->setAlignment(4);
    Value* add_sum = builder.CreateAdd(return_from_fib,sum_tmp);
    StoreInst* just_for_align_6 = builder.CreateStore(add_sum,main_return_value);
    just_for_align_6->setAlignment(4);
    builder.CreateBr(main_loop_iteration_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(main_loop_iteration_bb);
    LoadInst* count_tmp = builder.CreateLoad(main_count_value);
    count_tmp->setAlignment(4);
    Value* new_count = builder.CreateAdd(count_tmp,ConstantInt::get(Type::getInt32Ty(context),1,false));
    StoreInst* just_for_align_5 = builder.CreateStore(new_count,main_count_value);
    just_for_align_5->setAlignment(4);
    builder.CreateBr(main_loop_condition_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(main_exit_bb);
    LoadInst* final_return = builder.CreateLoad(main_return_value);
    final_return->setAlignment(4);
    builder.CreateRet(final_return);
    /********************************************************************************************/
    builder.SetInsertPoint(fib_init_condition_1_bb);
    AllocaInst* fib_return = builder.CreateAlloca(Type::getInt32Ty(context));
    fib_return->setAlignment(4);
    AllocaInst* fib_param = builder.CreateAlloca(Type::getInt32Ty(context));
    fib_param->setAlignment(4);
    //如何获取一个函数的参数呢
    //Function::
    StoreInst* just_for_align_4 = builder.CreateStore(fib_func->arg_begin(),fib_param);
    just_for_align_4->setAlignment(4);
    LoadInst* tmp_fib_param = builder.CreateLoad(fib_param);
    tmp_fib_param->setAlignment(4);
    Value* Cond_fib_1 = builder.CreateICmpEQ(tmp_fib_param,ConstantInt::get(Type::getInt32Ty(context),0,false));
    builder.CreateCondBr(Cond_fib_1,fib_then_body_1_bb,fib_condition_2_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(fib_then_body_1_bb);
    StoreInst* just_for_align_3 = builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context),0,false),fib_return);
    just_for_align_3->setAlignment(4);
    builder.CreateBr(fib_exit_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(fib_condition_2_bb);
    LoadInst* tmp_fib_param_2 = builder.CreateLoad(fib_param);
    tmp_fib_param_2->setAlignment(4);
    Value* Cond_fib_2 = builder.CreateICmpEQ(tmp_fib_param_2,ConstantInt::get(Type::getInt32Ty(context),1,false));
    builder.CreateCondBr(Cond_fib_2,fib_then_body_2_bb,fib_else_body_2_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(fib_then_body_2_bb);
    StoreInst* just_for_align_2 = builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context),1,false),fib_return);
    just_for_align_2->setAlignment(4);
    builder.CreateBr(fib_exit_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(fib_else_body_2_bb);

    LoadInst* fib_Lhs_1 = builder.CreateLoad(fib_param);
    fib_Lhs_1->setAlignment(4);
    Value* fib_Paratofib_1 = builder.CreateSub(fib_Lhs_1,ConstantInt::get(Type::getInt32Ty(context),1,false));
    std::vector<Value*> fib_Paratofibs_1;
    fib_Paratofibs_1.push_back(fib_Paratofib_1);
    Value* fib_in_return_1 = builder.CreateCall(fib_func,fib_Paratofibs_1);

    LoadInst* fib_Lhs_2 = builder.CreateLoad(fib_param);
    fib_Lhs_2->setAlignment(4);
    Value* fib_Paratofib_2 = builder.CreateSub(fib_Lhs_2,ConstantInt::get(Type::getInt32Ty(context),2,false));
    std::vector<Value*> fib_Paratofibs_2;
    fib_Paratofibs_2.push_back(fib_Paratofib_2);
    Value* fib_in_return_2 = builder.CreateCall(fib_func,fib_Paratofibs_2);

    Value* fib_in_final_return = builder.CreateAdd(fib_in_return_1,fib_in_return_2);
    StoreInst* just_for_align_1 = builder.CreateStore(fib_in_final_return,fib_return);
    just_for_align_1->setAlignment(4);
    builder.CreateBr(fib_exit_bb);
    /********************************************************************************************/
    builder.SetInsertPoint(fib_exit_bb);
    LoadInst* fib_final_return = builder.CreateLoad(fib_return);
    fib_final_return->setAlignment(4);
    builder.CreateRet(fib_final_return);

    module->print(outs(), nullptr);
    
    /**
    std::error_code EC;
    llvm::sys::fs::OpenFlags Flags;
    llvm::raw_fd_ostream OS("code_gen.ll", EC, Flags);
    module->print(OS, nullptr);
    OS.flush();
    module->dump();
    **/

    delete module;
    return 0;
}