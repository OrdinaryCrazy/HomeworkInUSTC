
// Generated from /home/crazy/3-compilerh/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "C1Parser.h"


namespace c1_recognizer {

/**
 * This interface defines an abstract listener for a parse tree produced by C1Parser.
 */
class  C1ParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCompilationUnit(C1Parser::CompilationUnitContext *ctx) = 0;
  virtual void exitCompilationUnit(C1Parser::CompilationUnitContext *ctx) = 0;

  virtual void enterDecl(C1Parser::DeclContext *ctx) = 0;
  virtual void exitDecl(C1Parser::DeclContext *ctx) = 0;

  virtual void enterConstdecl(C1Parser::ConstdeclContext *ctx) = 0;
  virtual void exitConstdecl(C1Parser::ConstdeclContext *ctx) = 0;

  virtual void enterConstdef(C1Parser::ConstdefContext *ctx) = 0;
  virtual void exitConstdef(C1Parser::ConstdefContext *ctx) = 0;

  virtual void enterVardecl(C1Parser::VardeclContext *ctx) = 0;
  virtual void exitVardecl(C1Parser::VardeclContext *ctx) = 0;

  virtual void enterVardef(C1Parser::VardefContext *ctx) = 0;
  virtual void exitVardef(C1Parser::VardefContext *ctx) = 0;

  virtual void enterFuncdef(C1Parser::FuncdefContext *ctx) = 0;
  virtual void exitFuncdef(C1Parser::FuncdefContext *ctx) = 0;

  virtual void enterBlock(C1Parser::BlockContext *ctx) = 0;
  virtual void exitBlock(C1Parser::BlockContext *ctx) = 0;

  virtual void enterStmt(C1Parser::StmtContext *ctx) = 0;
  virtual void exitStmt(C1Parser::StmtContext *ctx) = 0;

  virtual void enterLval(C1Parser::LvalContext *ctx) = 0;
  virtual void exitLval(C1Parser::LvalContext *ctx) = 0;

  virtual void enterCond(C1Parser::CondContext *ctx) = 0;
  virtual void exitCond(C1Parser::CondContext *ctx) = 0;

  virtual void enterRelop(C1Parser::RelopContext *ctx) = 0;
  virtual void exitRelop(C1Parser::RelopContext *ctx) = 0;

  virtual void enterExp(C1Parser::ExpContext *ctx) = 0;
  virtual void exitExp(C1Parser::ExpContext *ctx) = 0;

  virtual void enterNumber(C1Parser::NumberContext *ctx) = 0;
  virtual void exitNumber(C1Parser::NumberContext *ctx) = 0;

  virtual void enterBinop(C1Parser::BinopContext *ctx) = 0;
  virtual void exitBinop(C1Parser::BinopContext *ctx) = 0;

  virtual void enterUnaryop(C1Parser::UnaryopContext *ctx) = 0;
  virtual void exitUnaryop(C1Parser::UnaryopContext *ctx) = 0;


};

}  // namespace c1_recognizer
