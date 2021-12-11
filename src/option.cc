#include <iostream>
#include <string>
#include <config.h>
#include <syslog.h>
#include <option.h>
#include <stdint.h>

#include <gflags/gflags.h>
using namespace std;
using namespace gflags;

DEFINE_bool(test, false, "自动化测试");
DEFINE_string(text, "",  "输入表达式");

int option_init(int argc, char* argv[])
{
	int ret = 0;
	SetUsageMessage("表示式计算工具");
	SetVersionString(AntlrExpr_VERSION);
	ParseCommandLineFlags(&argc, &argv, true);
	return ret;
}
