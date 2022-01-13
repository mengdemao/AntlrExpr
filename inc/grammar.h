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
#include <config.h>
#include "ExprBaseVisitor.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "antlr4-runtime.h"
#include <ExprBaseListener.h>
#include <iostream>
#include <option.h>
#include <stack>
#include <string>
#include <test.h>
#include <svm.h>
#include <ast.h>

typedef enum {
	GRAMMAR_SUCCESS,	// 解析成功
	GRAMMAR_FAILURE, // 解析失败
} grammar_result;

using namespace antlr4;
using namespace tree;

#ifdef DEBUG_EXPR
#define TRACE()				\
do {						\
	std::cout << __func__ 	\
			  << "\t"		\
			  << __LINE__ 	\
			  << "\t"		\
			  << std::endl;	\
} while(0)
#else /* DEBUG_EXPR */
#define TRACE()	\
do {			\
} while(0)
#endif /* DEBUG_EXPR */

class ExprTreeListener : public ExprBaseListener
{
  public:

	void enterProg(ExprParser::ProgContext* ctx) override
	{
		// TRACE();
	}

	void exitProg(ExprParser::ProgContext* ctx) override
	{
		// TRACE();
	}

	void enterPrintExpr(ExprParser::PrintExprContext* ctx) override
	{
		// TRACE();
	}
	void exitPrintExpr(ExprParser::PrintExprContext* ctx) override
	{
		// TRACE();
	}

	void enterAssign(ExprParser::AssignContext* ctx) override
	{
		TRACE();
	}

	void exitAssign(ExprParser::AssignContext* ctx) override
	{
		TRACE();
	}

	void enterBlank(ExprParser::BlankContext* ctx) override
	{
		TRACE();
	}

	void exitBlank(ExprParser::BlankContext* ctx) override
	{
		TRACE();
	}

	void enterParens(ExprParser::ParensContext* ctx) override
	{
		TRACE();
	}

	void exitParens(ExprParser::ParensContext* ctx) override
	{
		TRACE();
	}

	void enterMulDiv(ExprParser::MulDivContext* ctx) override
	{
		TRACE();
	}

	void exitMulDiv(ExprParser::MulDivContext* ctx) override
	{
		TRACE();
	}

	void enterAddSub(ExprParser::AddSubContext* ctx) override
	{
		TRACE();
	}

	void exitAddSub(ExprParser::AddSubContext* ctx) override
	{
		TRACE();
	}

	void enterId(ExprParser::IdContext* ctx) override
	{
		TRACE();
	}

	void exitId(ExprParser::IdContext* ctx) override
	{
		TRACE();
	}

	void enterInt(ExprParser::IntContext* ctx) override
	{
		TRACE();
	}
	void exitInt(ExprParser::IntContext* ctx) override
	{
		TRACE();
	}

	void enterEveryRule(antlr4::ParserRuleContext* ctx) override
	{
		// TRACE();
	}
	void exitEveryRule(antlr4::ParserRuleContext* ctx) override
	{
		// TRACE();
	}

	void visitTerminal(antlr4::tree::TerminalNode* node) override
	{

	}

	void visitErrorNode(antlr4::tree::ErrorNode* node) override
	{

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
		std::string text = context->op->getText();
		return visitChildren(context);
	}

	antlrcpp::Any visitAddSub(ExprParser::AddSubContext* context)
	{
		std::string text = context->op->getText();
		return visitChildren(context);
	}

	antlrcpp::Any visitId(ExprParser::IdContext* context)
	{
		std::string text = context->ID()->getText();
		return visitChildren(context);
	}

	antlrcpp::Any visitInt(ExprParser::IntContext* context)
	{
		std::string text = context->INT()->getText();
		return visitChildren(context);
	}
};

grammar_result grammar_main(std::string InputString);

#endif /* __GRAMMAR_H__ */
