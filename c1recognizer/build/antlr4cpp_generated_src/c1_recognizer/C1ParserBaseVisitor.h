
// Generated from /home/crazy/3-compilerh/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "C1ParserVisitor.h"


namespace c1_recognizer {

/**
 * This class provides an empty implementation of C1ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  C1ParserBaseVisitor : public C1ParserVisitor {
public:

  virtual antlrcpp::Any visitCompilationUnit(C1Parser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecl(C1Parser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstdecl(C1Parser::ConstdeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstdef(C1Parser::ConstdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVardecl(C1Parser::VardeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVardef(C1Parser::VardefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncdef(C1Parser::FuncdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(C1Parser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmt(C1Parser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLval(C1Parser::LvalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCond(C1Parser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelop(C1Parser::RelopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExp(C1Parser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumber(C1Parser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinop(C1Parser::BinopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryop(C1Parser::UnaryopContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace c1_recognizer
