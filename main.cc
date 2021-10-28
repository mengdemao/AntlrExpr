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
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseListener.h"

using namespace antlr4;

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
    for (auto token : tokens.getTokens()) {
       std::cout << token->toString() << std::endl;
    }

    ExprParser parser(&tokens);
    tree::ParseTree* tree = parser.prog();

    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    return 0;
}

