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
#include <iostream>
#include <stack>
#include <string>

namespace proto {

// 65536
typedef enum {
	OP_NOP,	 //

	OP_MOV,	 //
	OP_LDR,	 //
	OP_STR,	 //
	
	OP_ADD,	 //
	OP_SUB,	 //
	OP_MUL,	 //
	OP_DIV,	 //
	OP_MOD,	 //
	OP_POW,	 //
	OP_UNM,	 //
	
	OP_AND,	 //
	OP_ORR,	 // 
	OP_NOT,  // 
	OP_XOR,  // 
	OP_EQU,  // 
	OP_NEQ,  // 
	
	OP_SHL,  // 
	OP_SHR,  // 
	
	OP_LEN,	 //

	OP_CAL,	 //
	OP_JMP,	 //
	OP_RET,	 //

	OP_OPEN,
	OP_READ,
	OP_CLOS,
	OP_PRTF,
	OP_MALC,
	OP_FREE,
	OP_MSET,
	OP_MCMP,
	OP_EXIT 
} op_code;

typedef uint32_t op_data;

/**
 * @brief 虚拟机指令码
 * 16 : op_code
 * 32 : op_data
 */
typedef struct {
	op_code code;
	op_data data;
} proto_code;

/**
 * @brief 
 */
typedef struct {
	std::string name;
	uint64_t data;
} proto_data;

/**
 * @brief 
 */
class svm
{
  public:
	svm();
	~svm() = default;

	void    psh(int32_t sym);
	int32_t pop(void);

	int	 call(proto_code pcode);
	void disp(void);

  private:
	std::stack<int32_t> call_stack;
};

/**
 * @brief 
 */
class proto {
  private:
	uint32_t ps;	// 指令个数
	uint32_t pc; 	// 指令计数器
	uint32_t lr;	// 连接计数器
	
	proto_code *pcode; 	// 代码段
	proto_data *pdata;	// 数据段
  
  public:
	proto();
	~proto() = default;

	void dump(std::string buffer);	/* 生成字符指令 */
	proto_code next(void);			/* 获取下一个指令 */
	void do_jmp(uint64_t pc);		/* 执行跳转 */
	void do_ret(void); 				/* 执行返回 */
	void do_cal(uint64_t pc); 		/* 函数调用 */
};

} // namespace proto

#endif /* __PROTO_H__ */