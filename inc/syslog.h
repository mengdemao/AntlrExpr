/**
 * @file syslog.h
 * @brief 日志打印打印
 * @version 0.0.0
 *
 */
#ifndef __SYSLOG_H__
#define __SYSLOG_H__

#define DEBUG_FUNC			\
do {						\
	std::cout << __func__ << "\t" << __LINE__ << std::endl;	\
} while(0);

#endif /* __SYSLOG_H__ */
