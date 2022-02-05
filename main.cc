/**
 * @file main.cc
 * @brief AntlrExpr主文件
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V1.0.0
 * @date 2021-10-23
 *
 *
 */
#include "ExprBaseVisitor.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprVisitor.h"
#include "antlr4-runtime.h"
#include <ExprBaseListener.h>
#include <ast.h>
#include <boost/iterator/iterator_facade.hpp>
#include <config.h>
#include <cstdlib>
#include <fmt/core.h>
#include <grammar.h>
#include <iostream>
#include <llvm.h>
#include <logger.h>
#include <option.h>
#include <proto.h>
#include <stack>
#include <string>

using namespace std;

/**
 * @brief 主函数
 * @param  argc 参数个数
 * @param  argv 参数列表
 * @return int  返回数据
 */
int main(int argc, char* argv[])
{
	string input_string;
	double input_result = 0;
	proto::proto proto_svm; 
	ast::ast_base ast_root;

	// avoid warning
	(void)input_result;

	llvm_init();

 	// 解析命令行参数
	if (OPTION_NONEUSE != option_main(argc, argv)) {
		return EXIT_FAILURE;
	}

	// TODO: 解析输入的数据作为参数使用
	input_string = argv[1];
	input_string.append("\n");

	// 生成语法树
	if (GRAMMAR_SUCCESS != grammar_main(input_string, ast_root)) {
		return EXIT_FAILURE;
	}

	// 执行程序
	std::cout << proto_svm.execute() << std::endl;

	return EXIT_SUCCESS;
}
