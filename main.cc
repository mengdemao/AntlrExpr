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
#include <llvm/Support/TargetSelect.h>
#include <option.h>
#include <stack>
#include <string>
#include <svm.h>
#include <test.h>

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

	// avoid warning
	(void)input_result;

	// llvm初始化
	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmParsers();
	llvm::InitializeAllAsmPrinters();

	// 解析命令行参数
	if (OPTION_NONEUSE != optionMain(argc, argv)) {
		return 0;
	}

	input_string = argv[1];
	input_string.append("\n");

	// 生成语法树
	if (GRAMMAR_SUCCESS != grammarMain(input_string)) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
