/**
 * @file grammar.h
 * @brief Expr语法处理文件
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V0.0.1
 * @date 2022-01-09
 *
 *
 */
#ifndef __GRAMMAR_H__
#define __GRAMMAR_H__
#include "ExprBaseVisitor.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "antlr4-runtime.h"
#include <ExprBaseListener.h>
#include <ast.h>
#include <config.h>
#include <iostream>
#include <option.h>
#include <stack>
#include <string>
#include <svm.h>
#include <test.h>

typedef enum {
	GRAMMAR_SUCCESS,  // 解析成功
	GRAMMAR_FAILURE,  // 解析失败
} grammar_result;

using namespace antlr4;
using namespace tree;

#ifdef DEBUG_EXPR
#define TRACE()                                                         \
	do {                                                                \
		std::cout << __func__ << "\t" << __LINE__ << "\t" << std::endl; \
	} while (0)
#else /* DEBUG_EXPR */
#define TRACE() \
	do {        \
	} while (0)
#endif /* DEBUG_EXPR */

class ExprTreeListener : public ExprBaseListener
{
  public:
	void enterProg(ExprParser::ProgContext* Ctx) override
	{
		// TRACE();
	}

	void exitProg(ExprParser::ProgContext* Ctx) override
	{
		// TRACE();
	}

	void enterPrintExpr(ExprParser::PrintExprContext* Ctx) override
	{
		// TRACE();
	}
	void exitPrintExpr(ExprParser::PrintExprContext* Ctx) override
	{
		// TRACE();
	}

	void enterAssign(ExprParser::AssignContext* Ctx) override
	{
		TRACE();
	}

	void exitAssign(ExprParser::AssignContext* Ctx) override
	{
		TRACE();
	}

	void enterBlank(ExprParser::BlankContext* Ctx) override
	{
		TRACE();
	}

	void exitBlank(ExprParser::BlankContext* Ctx) override
	{
		TRACE();
	}

	void enterParens(ExprParser::ParensContext* Ctx) override
	{
		TRACE();
	}

	void exitParens(ExprParser::ParensContext* Ctx) override
	{
		TRACE();
	}

	void enterMulDiv(ExprParser::MulDivContext* Ctx) override
	{
		TRACE();
	}

	void exitMulDiv(ExprParser::MulDivContext* Ctx) override
	{
		TRACE();
	}

	void enterAddSub(ExprParser::AddSubContext* Ctx) override
	{
		TRACE();
	}

	void exitAddSub(ExprParser::AddSubContext* Ctx) override
	{
		TRACE();
	}

	void enterId(ExprParser::IdContext* Ctx) override
	{
		TRACE();
	}

	void exitId(ExprParser::IdContext* Ctx) override
	{
		TRACE();
	}

	void enterInt(ExprParser::IntContext* Ctx) override
	{
		TRACE();
	}
	void exitInt(ExprParser::IntContext* Ctx) override
	{
		TRACE();
	}

	void enterEveryRule(antlr4::ParserRuleContext* Ctx) override
	{
		// TRACE();
	}
	void exitEveryRule(antlr4::ParserRuleContext* Ctx) override
	{
		// TRACE();
	}

	void visitTerminal(antlr4::tree::TerminalNode* Node) override
	{
		// TRACE();
	}

	void visitErrorNode(antlr4::tree::ErrorNode* Node) override
	{
		// TRACE();
	}
};

class ExprTreeVisitor : public ExprVisitor
{
  public:
	antlrcpp::Any visitProg(ExprParser::ProgContext* context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext* context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitAssign(ExprParser::AssignContext* context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitBlank(ExprParser::BlankContext* context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitParens(ExprParser::ParensContext* context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitMulDiv(ExprParser::MulDivContext* context)
	{
		std::string Text = context->op->getText();
		std::cout << Text << std::endl;
		return visitChildren(context);
	}

	antlrcpp::Any visitAddSub(ExprParser::AddSubContext* context)
	{
		std::string Text = context->op->getText();
		return visitChildren(context);
	}

	antlrcpp::Any visitId(ExprParser::IdContext* context)
	{
		std::string Text = context->ID()->getText();
		return visitChildren(context);
	}

	antlrcpp::Any visitInt(ExprParser::IntContext* context)
	{
		std::string Text = context->INT()->getText();
		return visitChildren(context);
	}
};

grammar_result grammarMain(std::string InputString);

#endif /* __GRAMMAR_H__ */
