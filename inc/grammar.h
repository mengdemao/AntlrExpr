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
#include "ExprBaseListener.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "antlr4-runtime.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <config.h>
#include <iostream>
#include <llvm.h>
#include <logger.h>
#include <option.h>
#include <proto.h>
#include <semantic.h>
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

	/**
	 * @fn void enterProg(ExprParser::ProgContext*)
	 * @brief
	 *
	 * @param ctx
	 */
	void enterProg(ExprParser::ProgContext* ctx) override;

	/**
     * @fn void exitProg(ExprParser::ProgContext*)
	 * @brief
	 *
	 * @param ctx
	 */
	void exitProg(ExprParser::ProgContext* ctx) override;

	/**
	 * @fn void enterPrintExpr(ExprParser::PrintExprContext*)
	 * @brief
	 *
	 * @param ctx
	 */
	void enterPrintExpr(ExprParser::PrintExprContext* ctx) override;

	/**
	 * @fn void exitPrintExpr(ExprParser::PrintExprContext*)
	 * @brief
	 *
	 * @param ctx
	 */
	void exitPrintExpr(ExprParser::PrintExprContext* ctx) override;

	/**
	 * @fn void enterAssign(ExprParser::AssignContext*)
	 * @brief
	 *
	 * @param ctx
	 */
	void enterAssign(ExprParser::AssignContext* ctx) override;
	void exitAssign(ExprParser::AssignContext* ctx) override;

	void enterBlank(ExprParser::BlankContext* ctx) override;
	void exitBlank(ExprParser::BlankContext* ctx) override;

	void enterParens(ExprParser::ParensContext* ctx) override;
	void exitParens(ExprParser::ParensContext* ctx) override;

	void enterMulDiv(ExprParser::MulDivContext* ctx) override;
	void exitMulDiv(ExprParser::MulDivContext* ctx) override;

	void enterAddSub(ExprParser::AddSubContext* ctx) override;
	void exitAddSub(ExprParser::AddSubContext* ctx) override;

	void enterId(ExprParser::IdContext* ctx) override;

	void exitId(ExprParser::IdContext* ctx) override;

	void enterInt(ExprParser::IntContext* ctx) override;
	void exitInt(ExprParser::IntContext* ctx) override;

	void enterEveryRule(antlr4::ParserRuleContext* ctx) override;
	void exitEveryRule(antlr4::ParserRuleContext* ctx) override;

	void visitTerminal(antlr4::tree::TerminalNode* node) override;
	void visitErrorNode(antlr4::tree::ErrorNode* node) override;
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

    /**
     * @fn antlrcpp::Any visitProg(ExprParser::ProgContext*)
     * @brief
     *
     * @param context
     * @return
     */
	antlrcpp::Any visitProg(ExprParser::ProgContext* context);

	/**
	 * @fn antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext* context);

	/**
	 * @fn antlrcpp::Any visitAssign(ExprParser::AssignContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitAssign(ExprParser::AssignContext* context);

	/**
	 * @fn antlrcpp::Any visitBlank(ExprParser::BlankContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitBlank(ExprParser::BlankContext* context);

	/**
	 * @fn antlrcpp::Any visitParens(ExprParser::ParensContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitParens(ExprParser::ParensContext* context);

	/**
	 * @fn antlrcpp::Any visitMulDiv(ExprParser::MulDivContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitMulDiv(ExprParser::MulDivContext* context);

	/**
	 * @fn antlrcpp::Any visitAddSub(ExprParser::AddSubContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitAddSub(ExprParser::AddSubContext* context);

	/**
	 * @fn antlrcpp::Any visitId(ExprParser::IdContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitId(ExprParser::IdContext* context);

	/**
	 * @fn antlrcpp::Any visitInt(ExprParser::IntContext*)
	 * @brief
	 *
	 * @param context
	 * @return
	 */
	antlrcpp::Any visitInt(ExprParser::IntContext* context);
};

/**
 * @brief  语法解析
 * @param  input_string     解析字符串
 * @param  ast_root         抽象语法树
 * @return grammar_result 
 */
extern grammar_result grammar_main(std::string input, proto::proto &proto);

#endif /* __GRAMMAR_H__ */
