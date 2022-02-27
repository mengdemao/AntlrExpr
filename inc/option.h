/**
 * @file option.h
 * @brief 解析输入字符串
 * @version V0.0.1
 *
 */
#ifndef __OPTION_H__
#define __OPTION_H__

#include <string>
typedef enum {
	OPTION_NONEUSE,	 // 不需要解析
	OPTION_SUCCESS,	 // 解析成功
	OPTION_FAILURE,	 // 解析失败
} option_result;

typedef struct {
	std::string input_string;
} option_value;

extern option_result option_main(int argc, char* argv[], option_value &value);

#endif /* __OPTION_H__ */
