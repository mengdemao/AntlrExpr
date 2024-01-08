
// Generated from /home/mengdemao/work/AntlrExpr/Expr.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ExprParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ExprParser.
 */
class  ExprListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(ExprParser::ProgContext *ctx) = 0;
  virtual void exitProg(ExprParser::ProgContext *ctx) = 0;

  virtual void enterPrintExpr(ExprParser::PrintExprContext *ctx) = 0;
  virtual void exitPrintExpr(ExprParser::PrintExprContext *ctx) = 0;

  virtual void enterAssign(ExprParser::AssignContext *ctx) = 0;
  virtual void exitAssign(ExprParser::AssignContext *ctx) = 0;

  virtual void enterBlank(ExprParser::BlankContext *ctx) = 0;
  virtual void exitBlank(ExprParser::BlankContext *ctx) = 0;

  virtual void enterParens(ExprParser::ParensContext *ctx) = 0;
  virtual void exitParens(ExprParser::ParensContext *ctx) = 0;

  virtual void enterMulDiv(ExprParser::MulDivContext *ctx) = 0;
  virtual void exitMulDiv(ExprParser::MulDivContext *ctx) = 0;

  virtual void enterAddSub(ExprParser::AddSubContext *ctx) = 0;
  virtual void exitAddSub(ExprParser::AddSubContext *ctx) = 0;

  virtual void enterId(ExprParser::IdContext *ctx) = 0;
  virtual void exitId(ExprParser::IdContext *ctx) = 0;

  virtual void enterInt(ExprParser::IntContext *ctx) = 0;
  virtual void exitInt(ExprParser::IntContext *ctx) = 0;


};

