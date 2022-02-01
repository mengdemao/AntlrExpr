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

enum LOG_LEVEL {
	LL_TRACE,
	LL_DEBUG,
	LL_INFO,
	LL_WARNING,
	LL_ERROR,
	LL_CRITICAL
};

#define log_print()		std::cout << "[" << __FILE__ << "]" << "[" << __LINE__ << "]" << "[" << __func__ << "] "

#define log_trace() 	log_print()
#define log_debug() 	log_print()
#define log_info() 		log_print()
#define log_warning() 	log_print()
#define log_error() 	log_print()
#define log_critical() 	log_print()

#endif /* __LOGGER_H__ */