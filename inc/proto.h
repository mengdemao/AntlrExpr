/**
 * @file proto.h
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.1
 * @date 2022-01-30
 * 
 * @brief 代码生成
 * 
 * @copyright Copyright (c) 2022  mengdemao
 * 
 */
#ifndef __PROTO_H__
#define __PROTO_H__

#include <cstdint>
#include <string>

typedef uint64_t code;

typedef struct data {
	std::string name;
	uint64_t data;
} data;

class proto {
  private:
	uint64_t pc; 	// 指令计数器
	uint64_t lr;	// 连接计数器

	code *pcode; 	// 代码段
	data *pdata;	// 数据段
  
  public:
	proto();
	~proto() = default;

	code next(void);			/* 获取下一个指令 */
	void do_jmp(uint64_t pc);	/* 执行跳转 */
	void do_ret(void); 			/* 执行返回 */
	void do_cal(uint64_t pc); 	/* 函数调用 */
};

#endif /* __PROTO_H__ */