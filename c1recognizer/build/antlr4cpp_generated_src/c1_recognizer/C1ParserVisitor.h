
// Generated from /home/crazy/3-compilerh/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "C1Parser.h"


namespace c1_recognizer {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by C1Parser.
 */
class  C1ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by C1Parser.
   */
    virtual antlrcpp::Any visitCompilationUnit(C1Parser::CompilationUnitContext *context) = 0;

    virtual antlrcpp::Any visitDecl(C1Parser::DeclContext *context) = 0;

    virtual antlrcpp::Any visitConstdecl(C1Parser::ConstdeclContext *context) = 0;

    virtual antlrcpp::Any visitConstdef(C1Parser::ConstdefContext *context) = 0;

    virtual antlrcpp::Any visitVardecl(C1Parser::VardeclContext *context) = 0;

    virtual antlrcpp::Any visitVardef(C1Parser::VardefContext *context) = 0;

    virtual antlrcpp::Any visitFuncdef(C1Parser::FuncdefContext *context) = 0;

    virtual antlrcpp::Any visitBlock(C1Parser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitStmt(C1Parser::StmtContext *context) = 0;

    virtual antlrcpp::Any visitLval(C1Parser::LvalContext *context) = 0;

    virtual antlrcpp::Any visitCond(C1Parser::CondContext *context) = 0;

    virtual antlrcpp::Any visitRelop(C1Parser::RelopContext *context) = 0;

    virtual antlrcpp::Any visitExp(C1Parser::ExpContext *context) = 0;

    virtual antlrcpp::Any visitNumber(C1Parser::NumberContext *context) = 0;

    virtual antlrcpp::Any visitBinop(C1Parser::BinopContext *context) = 0;

    virtual antlrcpp::Any visitUnaryop(C1Parser::UnaryopContext *context) = 0;


};

}  // namespace c1_recognizer
