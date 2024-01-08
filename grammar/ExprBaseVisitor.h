
// Generated from /home/mengdemao/work/AntlrExpr/Expr.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ExprVisitor.h"


/**
 * This class provides an empty implementation of ExprVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ExprBaseVisitor : public ExprVisitor {
public:

  virtual std::any visitProg(ExprParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintExpr(ExprParser::PrintExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign(ExprParser::AssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlank(ExprParser::BlankContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParens(ExprParser::ParensContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDiv(ExprParser::MulDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSub(ExprParser::AddSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitId(ExprParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInt(ExprParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }


};

