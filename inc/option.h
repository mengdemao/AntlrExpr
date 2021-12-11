/**
 * @file option.h
 * @brief 解析输入字符串
 * @version V0.0.1
 *
 */
#ifndef __OPTION_H__
#define __OPTION_H__

#include <gflags/gflags.h>
using namespace gflags;

DECLARE_bool(test);
DECLARE_string(text);

extern int option_init(int argc, char* argv[]);

#endif /* __OPTION_H__ */
