/**
 * @file main.cc
 * @brief AntlrExpr主文件
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V0.0.0
 * @date 2021-10-23
 *
 *
 */
#include <config.h>
#include <ExprBaseListener.h>
#include "ExprBaseVisitor.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "antlr4-runtime.h"
#include <iostream>
#include <option.h>
#include <string>
#include <syslog.h>
#include <test.h>

using namespace antlr4;
using namespace tree;
using namespace std;

class ExprTreeListener : public ExprBaseListener
{
    private:
    stack<double> ExprStack;

    public:
    void enterProg(ExprParser::ProgContext* ctx) override {}
    void exitProg(ExprParser::ProgContext* ctx) override {}
    void enterPrintExpr(ExprParser::PrintExprContext* ctx) override {}
    void exitPrintExpr(ExprParser::PrintExprContext* ctx) override {}

    void enterAssign(ExprParser::AssignContext* ctx) override {}

    void exitAssign(ExprParser::AssignContext* ctx) override {}

    void enterBlank(ExprParser::BlankContext* ctx) override {}

    void exitBlank(ExprParser::BlankContext* ctx) override {}

    void enterParens(ExprParser::ParensContext* ctx) override {}

    void exitParens(ExprParser::ParensContext* ctx) override {}

    void enterMulDiv(ExprParser::MulDivContext* ctx) override {}

    void exitMulDiv(ExprParser::MulDivContext* ctx) override {}

    void enterAddSub(ExprParser::AddSubContext* ctx) override {}

    void exitAddSub(ExprParser::AddSubContext* ctx) override {}

    void enterId(ExprParser::IdContext* ctx) override {}

    void exitId(ExprParser::IdContext* ctx) override {}

    void enterInt(ExprParser::IntContext* ctx) override {}
    void exitInt(ExprParser::IntContext* ctx) override {}

    void enterEveryRule(antlr4::ParserRuleContext* ctx) override {}
    void exitEveryRule(antlr4::ParserRuleContext* ctx) override {}

    void visitTerminal(antlr4::tree::TerminalNode* node) override;
    void visitErrorNode(antlr4::tree::ErrorNode* node) override;
};

void ExprTreeListener::visitErrorNode(antlr4::tree::ErrorNode* node)
{
    std::string getText = node->getText();
    if (!getText.empty()) {
    }
}

void ExprTreeListener::visitTerminal(antlr4::tree::TerminalNode* node)
{
    std::string getText = node->getText();
    if (getText != "\n") {
    }
}

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

/**
 * @brief 主函数
 * @param  argc 参数个数
 * @param  argv 参数列表
 * @return int  返回数据
 */
int main(int argc, char* argv[])
{
    syslog syslog;
    string InputString;
    double InputResult = 0;
    double result_walker = 0;
    double result_visitor = 0;

    // avoid warning
    (void)InputResult;
    (void)result_walker;
    (void)result_visitor;

    // 解析命令行参数
    (void)option_init(argc, argv);

    // 输入字符串
    if (FLAGS_test) {
	TestExpr TestExpr;
	InputString = TestExpr.GetExpr();
	InputResult = TestExpr.GetResult();
    } else {
	InputString = string(FLAGS_text);
    }

    // 追加结束符
    InputString.append("\n");

    // 生成解析字符串
    ANTLRInputStream input(InputString);

    // 词法解析
    ExprLexer lexer(&input);

    // 分割单词
    CommonTokenStream tokens(&lexer);

    // 解析语法单元
    ExprParser parser(&tokens);

    // 生成语法树
    ParseTree* tree = parser.prog();

    // 1. Listener模式解析语法树
    ExprTreeListener listener;
    ParseTreeWalker	 walker;
    walker.walk(&listener, tree);

    // 2. Visitor模式解析语法树
    ExprTreeVisitor visitor;
    visitor.visit(tree);

    // 处于自动化测试状态下返回状态
    if (FLAGS_test) {
	std::cout << "AntlrExpr Test Success" << std::endl;
	return 0;
    }

    return 0;
}
