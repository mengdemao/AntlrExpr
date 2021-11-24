/**
 * @file main.cc
 * @brief AntlrExpr主文件
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V0.0.0
 * @date 2021-10-23
 *
 *
 */
#include <iostream>
#include <string>
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseListener.h"

#include <config.h>
#include <syslog.h>
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "ExprBaseVisitor.h"
#include "ExprBaseListener.h"

using namespace antlr4;
using namespace tree;

class ExprTreeListener : public ExprBaseListener {
public:
	void enterProg(ExprParser::ProgContext *ctx) override
	{
	}
	void exitProg(ExprParser::ProgContext *ctx) override
	{
	}
	void enterPrintExpr(ExprParser::PrintExprContext *ctx) override
	{
	}
	void exitPrintExpr(ExprParser::PrintExprContext *ctx) override
	{
	}

	void enterAssign(ExprParser::AssignContext *ctx) override
	{
		std::cout << __func__ << "\t" << ctx->ID()->getText() << std::endl;
	}

	void exitAssign(ExprParser::AssignContext *ctx) override
	{
		std::cout << __func__ << "\t" << ctx->ID()->getText() << std::endl;
	}

	void enterBlank(ExprParser::BlankContext *ctx) override
	{
	}

	void exitBlank(ExprParser::BlankContext *ctx) override
	{
	}

	void enterParens(ExprParser::ParensContext *ctx) override
	{
	}

	void exitParens(ExprParser::ParensContext *ctx) override
	{
	}

	void enterMulDiv(ExprParser::MulDivContext *ctx) override
	{
		if (ctx->op->getType() == ExprParser::MUL) {
			std::cout << __func__ << "\t" << ctx->MUL()->getText() << std::endl;
		} else {
			std::cout << __func__ << "\t" << ctx->DIV()->getText() << std::endl;
		}
	}

	void exitMulDiv(ExprParser::MulDivContext *ctx) override
	{
		if (ctx->op->getType() == ExprParser::MUL) {
			std::cout << __func__ << "\t" << ctx->MUL()->getText() << std::endl;
		} else {
			std::cout << __func__ << "\t" << ctx->DIV()->getText() << std::endl;
		}
	}

	void enterAddSub(ExprParser::AddSubContext *ctx) override
	{
		if (ctx->op->getType() == ExprParser::ADD) {
			std::cout << __func__ << "\t" << ctx->ADD()->getText() << std::endl;
		} else {
			std::cout << __func__ << "\t" << ctx->SUB()->getText() << std::endl;
		}
	}

	void exitAddSub(ExprParser::AddSubContext *ctx) override
	{
		if (ctx->op->getType() == ExprParser::ADD) {
			std::cout << __func__ << "\t" << ctx->ADD()->getText() << std::endl;
		} else {
			std::cout << __func__ << "\t" << ctx->SUB()->getText() << std::endl;
		}
	}

	void enterId(ExprParser::IdContext *ctx) override
	{
		std::cout << __func__ << "\t" << ctx->ID()->getText() << std::endl;
	}

	void exitId(ExprParser::IdContext *ctx) override
	{
		std::cout << __func__ << "\t\t" << ctx->ID()->getText() << std::endl;
	}

	void enterInt(ExprParser::IntContext *ctx) override
	{
		std::cout << __func__ << "\t" << ctx->INT()->toString() << std::endl;
	}
	void exitInt(ExprParser::IntContext *ctx) override
	{
		std::cout << __func__ << "\t\t" << ctx->INT()->toString() << std::endl;
	}

	void enterEveryRule(antlr4::ParserRuleContext *ctx) override
	{
	}
	void exitEveryRule(antlr4::ParserRuleContext *ctx) override
	{
	}

	void visitTerminal(antlr4::tree::TerminalNode *node) override;
	void visitErrorNode(antlr4::tree::ErrorNode *node) override;
};

void ExprTreeListener::visitErrorNode(antlr4::tree::ErrorNode *node)
{
	std::cout << __func__ << "\t" << node->getText() << std::endl;
}

void ExprTreeListener::visitTerminal(antlr4::tree::TerminalNode *node)
{
	std::cout << __func__ << "\t" << node->getText() << std::endl;
}

class ExprTreeVisitor : public ExprVisitor {
public:
	antlrcpp::Any visitProg(ExprParser::ProgContext *context)
	{
		std::cout << __func__ << __LINE__ << std::endl;
		this->visit(context);
		std::cout << __func__ << __LINE__ << std::endl;
		return 0;
	}

	antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext *context)
	{
		this->visit(context);
		return 0;
	}

	antlrcpp::Any visitAssign(ExprParser::AssignContext *context)
	{
		this->visit(context);
		return 0;
	}

	antlrcpp::Any visitBlank(ExprParser::BlankContext *context)
	{
		return 0;
	}

	antlrcpp::Any visitParens(ExprParser::ParensContext *context)
	{
		return 0;
	}

	antlrcpp::Any visitMulDiv(ExprParser::MulDivContext *context)
	{
		std::string text = context->op->getText();
		std::cout << __func__ << "\t" << text << std::endl;
		this->visit(context);
		return 0;
	}

	antlrcpp::Any visitAddSub(ExprParser::AddSubContext *context)
	{
		std::string text = context->op->getText();
		std::cout << __func__ << "\t" << text << std::endl;
		this->visit(context);

		return 0;
	}

	antlrcpp::Any visitId(ExprParser::IdContext *context)
	{
		return 0;
	}

	antlrcpp::Any visitInt(ExprParser::IntContext *context)
	{
		return 0;
	}
};

/**
 * @brief 主函数
 * @param  argc 参数个数
 * @param  argv 参数列表
 * @return int  返回数据
 */
int main(int argc, const char *argv[])
{
	if (!argv[1])
	{
		std::cout << "Antlr expr version " << AntlrExpr_VERSION << std::endl;
		std::cout << "Please input expression" << std::endl;
		return -1;
	}
	std::string InputString(argv[1]);
	InputString.append("\n");

	// 输入字符串
	ANTLRInputStream input(InputString);

	// 词法解析
	ExprLexer lexer(&input);

	// 分割单词
	CommonTokenStream tokens(&lexer);

	// 解析语法单元
	ExprParser parser(&tokens);

	// 生成语法树
	ParseTree *tree = parser.prog();

	// 1. Listener
	std::cout << "Listener mode start" << std::endl;
	ExprTreeListener listener;
	ParseTreeWalker walker;
	walker.walk(&listener, tree);
	std::cout << "Listener mode end" << std::endl;

	// 2. Visitor
	std::cout << "Visitor mode start" << std::endl;
	ExprTreeVisitor visitor;
	visitor.visit(tree);
	std::cout << "Visitor mode end" << std::endl;
	return 0;
}
