/**
 * @file option.cc
 * @author mengdemao (mengdemao@163.com)
 * @brief 解析输入的命令行
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <config.h>
#include <iostream>
#include <option.h>
#include <stdint.h>
#include <string>
#include <syslog.h>
#include <version.h>

#define STRIP_FLAG_HELP 1
#include <gflags/gflags.h>

using namespace std;
using namespace gflags;

DEFINE_bool(test, false, "自动化测试");
DEFINE_string(text, "", "输入表达式");

/**
 * @brief 解析输入的命令行
 *
 * @param argc 输入参数个数
 * @param argv 输入参数内容
 * @return int 执行结果
 */
int option_init(int argc, char* argv[])
{
	int ret = 0;
	SetUsageMessage("表示式计算工具");
	SetVersionString(AntlrExpr_VERSION);
	ParseCommandLineFlags(&argc, &argv, false);
	return ret;
}
