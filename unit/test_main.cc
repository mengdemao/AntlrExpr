#include <gtest/gtest.h>
#include <iostream>

#include "test_gtest.cc"
#include "test_ast.cc"
#include "test_proto.cc"

/**
 * @brief  测试主函数
 * @param  argc #
 * @param  argv #
 * @return int 测试结果
 */
int main(int argc, char *argv[])
{
	test_gtest();
	
	test_ast();

	test_proto();

	return 0;
}