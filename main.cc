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
#include <boost/iterator/iterator_facade.hpp>
#include <config.h>
#include <cstdlib>
#include <grammar.h>
#include <iostream>
#include <logger.h>
#include <option.h>
#include <proto.h>
#include <stack>
#include <string>

/**
 * @brief 主函数
 * @param  argc 参数个数
 * @param  argv 参数列表
 * @return int  返回数据
 */
int main(int argc, char* argv[])
{
	std::string input_string;
	double input_result = 0;
	proto::proto proto_svm;

	// avoid warning
	(void)input_result;

	// 解析命令行参数
	option_value option_value;
	option_result option_result = option_main(argc, argv, option_value);
	if (OPTION_NONEUSE == option_result) {
		input_string = argv[1];
		input_string.append("\n");
	} else if (OPTION_SUCCESS == option_result) {
		input_string = option_value.input_string;
	} else {
		return EXIT_FAILURE;
	}

	const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	// 语义分析与代码生成
	if (GRAMMAR_SUCCESS != grammar_main(input_string, proto_svm)) {
		return EXIT_FAILURE;
	}

	// 执行程序
	int result = proto_svm.execute();

	std::cout << "execute\t" << result << std::endl;

	const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	const auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Compilation Time: " << elapsed_time.count() << " microseconds\n";

	return EXIT_SUCCESS;
}
