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
	}

	void exitAssign(ExprParser::AssignContext *ctx) override
	{
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
	}

	void exitMulDiv(ExprParser::MulDivContext *ctx) override
	{
	}

	void enterAddSub(ExprParser::AddSubContext *ctx) override
	{
	}

	void exitAddSub(ExprParser::AddSubContext *ctx) override
	{
	}

	void enterId(ExprParser::IdContext *ctx) override
	{
	}

	void exitId(ExprParser::IdContext *ctx) override
	{
	}

	void enterInt(ExprParser::IntContext *ctx) override
	{
	}
	void exitInt(ExprParser::IntContext *ctx) override
	{
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
	std::string getText = node->getText();
	if (!getText.empty())
	{
		std::cout << __func__ << "\t" << node->getText() << std::endl;
	}
}

void ExprTreeListener::visitTerminal(antlr4::tree::TerminalNode *node)
{
	std::string getText = node->getText();
	if (getText != "\n")
	{
		std::cout << __func__ << "\t" << node->getText() << std::endl;
	}
}

class ExprTreeVisitor : public ExprVisitor {
public:
	antlrcpp::Any visitProg(ExprParser::ProgContext *context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext *context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitAssign(ExprParser::AssignContext *context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitBlank(ExprParser::BlankContext *context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitParens(ExprParser::ParensContext *context)
	{
		return visitChildren(context);
	}

	antlrcpp::Any visitMulDiv(ExprParser::MulDivContext *context)
	{
		std::string text = context->op->getText();
		std::cout << __func__ << "\t" << text << std::endl;
		return visitChildren(context);
	}

	antlrcpp::Any visitAddSub(ExprParser::AddSubContext *context)
	{
		std::string text = context->op->getText();
		std::cout << __func__ << "\t" << text << std::endl;
		return visitChildren(context);
	}

	antlrcpp::Any visitId(ExprParser::IdContext *context)
	{
		std::string text = context->ID()->getText();
		std::cout << __func__ << "\t" << text << std::endl;
		return visitChildren(context);
	}

	antlrcpp::Any visitInt(ExprParser::IntContext *context)
	{
		std::string text = context->INT()->getText();
		std::cout << __func__ << "\t" << text << std::endl;
		return visitChildren(context);
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
	if (!argv[1]) {
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
	std::cout << "Listener mode end\n" << std::endl;

	// 2. Visitor
	std::cout << "Visitor mode start" << std::endl;
	ExprTreeVisitor visitor;
	visitor.visit(tree);
	std::cout << "Visitor mode end\n" << std::endl;
	return 0;
}
