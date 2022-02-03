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
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <ExprBaseListener.h>
#include <ast.h>
#include <config.h>
#include <iostream>
#include <llvm.h>
#include <option.h>
#include <stack>
#include <string>

typedef enum {
	GRAMMAR_SUCCESS,  // 解析成功
	GRAMMAR_FAILURE,  // 解析失败
} grammar_result;

using namespace antlr4;
using namespace tree;

class expr_listener : public ExprBaseListener
{
  public:
	void enterProg(ExprParser::ProgContext* ctx) override
	{
	}

	void exitProg(ExprParser::ProgContext* ctx) override
	{
	}

	void enterPrintExpr(ExprParser::PrintExprContext* ctx) override
	{
	}
	void exitPrintExpr(ExprParser::PrintExprContext* ctx) override
	{
	}

	void enterAssign(ExprParser::AssignContext* ctx) override
	{
	}

	void exitAssign(ExprParser::AssignContext* ctx) override
	{
	}

	void enterBlank(ExprParser::BlankContext* ctx) override
	{
	}

	void exitBlank(ExprParser::BlankContext* ctx) override
	{
	}

	void enterParens(ExprParser::ParensContext* ctx) override
	{
	}

	void exitParens(ExprParser::ParensContext* ctx) override
	{
	}

	void enterMulDiv(ExprParser::MulDivContext* ctx) override
	{
	}

	void exitMulDiv(ExprParser::MulDivContext* ctx) override
	{
	}

	void enterAddSub(ExprParser::AddSubContext* ctx) override
	{
	}

	void exitAddSub(ExprParser::AddSubContext* ctx) override
	{
	}

	void enterId(ExprParser::IdContext* ctx) override
	{
	}

	void exitId(ExprParser::IdContext* ctx) override
	{
	}

	void enterInt(ExprParser::IntContext* ctx) override
	{
	}
	void exitInt(ExprParser::IntContext* ctx) override
	{
	}

	void enterEveryRule(antlr4::ParserRuleContext* ctx) override
	{
	}
	void exitEveryRule(antlr4::ParserRuleContext* ctx) override
	{
	}

	void visitTerminal(antlr4::tree::TerminalNode* node) override
	{
	}

	void visitErrorNode(antlr4::tree::ErrorNode* node) override
	{
	}
};

class expr_visitor : public ExprVisitor
{
  private:
	std::unique_ptr<llvm::LLVMContext> llvm_context;
	llvm::IRBuilder<>				   builder;
	std::unique_ptr<llvm::Module>	   module;
	std::vector<scope>				   scopes;

  public:
	expr_visitor() : llvm_context(std::make_unique<llvm::LLVMContext>()), 
						builder(*this->llvm_context), 
						module(std::make_unique<llvm::Module>("output", *this->llvm_context)) 
	{
		/* No return */
	}

	scope &current_scope();

    llvm::Value *get_variable(const std::string &name);

    void read_buffer(const std::string &buffer);

    llvm::Function *print_proto();

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

grammar_result grammar_main(std::string input_string);

#endif /* __GRAMMAR_H__ */