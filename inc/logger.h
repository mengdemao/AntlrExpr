/**
 * @file logger.h
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2022-01-30
 * 
 * @brief 日志打印封装
 * 
 * @copyright Copyright (c) 2022  mengdemao
 * 
 */
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fmt/color.h>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/printf.h>

enum log_level {
	LL_TRACE,
	LL_DEBUG,
	LL_INFO,
	LL_WARNING,
	LL_ERROR,
	LL_CRITICAL
};

// #define log_print(level, format, __VA_ARGS__)	\
// ({ \
// 	std::string head = fmt::format("[{0}][{1}][{2}]", __FILE__, __func__, __LINE__); \
// 	std::string text = fmt::format(format, __VA_ARGS__); \
// 	std::string tail = "\r\n"; \
// 	fmt::print("{0} {1} {2}", head, text, tail);\
// })

// #define log_trace(format, ...) 		log_print(LL_TRACE, 	format, __VA_ARGS__)
// #define log_debug(format, ...) 		log_print(LL_DEBUG, 	format, __VA_ARGS__)
// #define log_info(format, ...) 		log_print(LL_INFO, 		format, __VA_ARGS__)
// #define log_warning(format, ...) 	log_print(LL_WARNING, 	format, __VA_ARGS__)
// #define log_error(format, ...) 		log_print(LL_ERROR, 	format, __VA_ARGS__)
// #define log_critical(format, ...) 	log_print(LL_CRITICAL, 	format, __VA_ARGS__)

#define log_trace fmt::print("[{}][{}]:\t",__func__, __LINE__); fmt::print
#define log_debug fmt::print("[{}][{}]:\t", __func__, __LINE__); fmt::print
#define log_info fmt::print("[{}][{}]:\t", __func__, __LINE__); fmt::print
#define log_warning fmt::print("[{}][{}]:\t", __func__, __LINE__); fmt::print
#define log_error fmt::print("[{}][{}]:\t",  __func__, __LINE__); fmt::print
#define log_critical fmt::print("[{}][{}]:\t", __func__, __LINE__); fmt::print

#endif /* __LOGGER_H__ */
