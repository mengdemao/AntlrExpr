#include <gtest/gtest.h>
#include <iostream>

#include "test_gtest.cc"
#include "test_proto.cc"

/**
 * @fn int main(int, char*[])
 * @brief 测试函数主程序
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
  	testing::InitGoogleTest(&argc, argv);

  	return RUN_ALL_TESTS();
}
