
// Generated from /home/mengdemao/work/AntlrExpr/Expr.g4 by ANTLR 4.9.2

#pragma once

#include "ExprVisitor.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of ExprVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class ExprBaseVisitor : public ExprVisitor
{
  public:
	virtual antlrcpp::Any visitProg(ExprParser::ProgContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitAssign(ExprParser::AssignContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitBlank(ExprParser::BlankContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitParens(ExprParser::ParensContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitMulDiv(ExprParser::MulDivContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitAddSub(ExprParser::AddSubContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitId(ExprParser::IdContext* ctx) override
	{
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitInt(ExprParser::IntContext* ctx) override
	{
		return visitChildren(ctx);
	}
};
