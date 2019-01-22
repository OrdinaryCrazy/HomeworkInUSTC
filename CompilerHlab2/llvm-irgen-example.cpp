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
#include <fstream>

using namespace llvm;

int main()
{
    LLVMContext context;
    IRBuilder<> builder(context);

    auto module = new Module("foo_dead_recursive_loop", context);

    auto func = Function::Create(FunctionType::get(Type::getVoidTy(context), std::vector<Type *>(), false),
                                 GlobalValue::LinkageTypes::ExternalLinkage,
                                 "foo", module);
    auto bb = BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(bb);
    builder.CreateCall(func, {});
    builder.CreateRetVoid();
    builder.ClearInsertionPoint();

    //std::fstream outfile;
    //outfile.open("./testout.txt",std::ios::out);
    module->print(outs(), nullptr);
    //module->print(outfile, nullptr);
    //outfile<< *module ;
    //outfile.close();
    //module->dump();

    delete module;
    return 0;
}