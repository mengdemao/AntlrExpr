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
#include "ExprBaseVisitor.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "antlr4-runtime.h"
#include <ExprBaseListener.h>
#include <cstdlib>
#include <iostream>
#include <option.h>
#include <stack>
#include <string>
#include <test.h>
#include <svm.h>
#include <ast.h>
#include <grammar.h>

using namespace std;

/**
 * @brief 主函数
 * @param  argc 参数个数
 * @param  argv 参数列表
 * @return int  返回数据
 */
int main(int argc, char* argv[])
{
	string InputString;
	double InputResult	  = 0;

	// avoid warning
	(void)InputResult;

	// 解析命令行参数
	if (OPTION_NONEUSE != option_main(argc, argv))
	{
		return 0;
	}

	InputString = argv[1];
	InputString.append("\n");

	if (GRAMMAR_SUCCESS != grammar_main(InputString))
	{
		return EXIT_FAILURE;
	}

	return 0;
}
