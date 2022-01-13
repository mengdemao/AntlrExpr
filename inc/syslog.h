/**
 * @file syslog.h
 * @brief 日志打印打印
 * @version 0.0.0
 *
 */
#ifndef __SYSLOG_H__
#define __SYSLOG_H__

class syslog
{
  private:
	bool init;  // 链接状态
	int	addr;  // IP地址
	int	port;  // 端口号

	int rank;  // 打印等级

  public:
	enum {
		LOG_ALERT,
		LOG_ERROR,
		LOG_WARNING,
		LOG_DEBUG,
		LOG_TRACE,
	};

	syslog(int addr, int port, int rank);

	~syslog();

	bool connect(void);
	bool print(void);
	bool hexdump(void);
};

#endif /* __SYSLOG_H__ */
