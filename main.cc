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
#include "ExprBaseListener.h"

using namespace antlr4;

class ExprTreeListener : public ExprBaseListener {
public:
	  void enterProg(ExprParser::ProgContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitProg(ExprParser::ProgContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterPrintExpr(ExprParser::PrintExprContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitPrintExpr(ExprParser::PrintExprContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterAssign(ExprParser::AssignContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitAssign(ExprParser::AssignContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterBlank(ExprParser::BlankContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitBlank(ExprParser::BlankContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterParens(ExprParser::ParensContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitParens(ExprParser::ParensContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterMulDiv(ExprParser::MulDivContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitMulDiv(ExprParser::MulDivContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterAddSub(ExprParser::AddSubContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitAddSub(ExprParser::AddSubContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterId(ExprParser::IdContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitId(ExprParser::IdContext *ctx) override
	  {
		  DEBUG_FUNC
	  }

	  void enterInt(ExprParser::IntContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitInt(ExprParser::IntContext *ctx) override
	  {
		  DEBUG_FUNC
	  }


	  void enterEveryRule(antlr4::ParserRuleContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void exitEveryRule(antlr4::ParserRuleContext *ctx) override
	  {
		  DEBUG_FUNC
	  }
	  void visitTerminal(antlr4::tree::TerminalNode *node) override
	  {
		  DEBUG_FUNC
	  }
	  void visitErrorNode(antlr4::tree::ErrorNode *node) override
	  {
		  DEBUG_FUNC
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

    ANTLRInputStream input(InputString);
    ExprLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    /*
    for (auto token : tokens.getTokens()) {
       std::cout << token->toString() << std::endl;
    }
	*/

    ExprParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();

    // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    ExprTreeListener listener;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    return 0;
}

