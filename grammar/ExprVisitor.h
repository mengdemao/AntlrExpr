
// Generated from /home/mengdemao/work/AntlrExpr/Expr.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ExprParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ExprParser.
 */
class  ExprVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ExprParser.
   */
    virtual antlrcpp::Any visitProg(ExprParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext *context) = 0;

    virtual antlrcpp::Any visitAssign(ExprParser::AssignContext *context) = 0;

    virtual antlrcpp::Any visitBlank(ExprParser::BlankContext *context) = 0;

    virtual antlrcpp::Any visitParens(ExprParser::ParensContext *context) = 0;

    virtual antlrcpp::Any visitMulDiv(ExprParser::MulDivContext *context) = 0;

    virtual antlrcpp::Any visitAddSub(ExprParser::AddSubContext *context) = 0;

    virtual antlrcpp::Any visitId(ExprParser::IdContext *context) = 0;

    virtual antlrcpp::Any visitInt(ExprParser::IntContext *context) = 0;


};

