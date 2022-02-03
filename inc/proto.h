/**
 * @file proto.h
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.1
 * @date 2022-01-30
 * 
 * @brief 代码生成与虚拟机实现
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
#include <vector>

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
	OP_RET,  // 

	OP_OPEN, // 打开
	OP_READ, // 读取
	OP_CLOS, // 关闭
	OP_PRTF, // 打印
	OP_MALC, // 内存申请
	OP_FREE,
	OP_MSET,
	OP_MCMP,
	OP_EXIT 
} op_code;

typedef uint16_t op_cond;
typedef uint32_t op_data;

/**
 * @brief 虚拟机指令码
 * 16 : op_code
 * 32 : op_data
 */
typedef struct {
	op_code code;
	op_cond cond;
	op_data data;
} proto_code;

/**
 * @brief 全局变量描述
 */
typedef struct {
	std::string name;
	uint64_t data;
} proto_data;

/**
 * @brief 虚拟机标志位
 */
typedef struct {
	uint64_t none;
} svm_flags;

class proto;

/**
 * @brief 
 */
class svm
{
  public:
	svm(proto *sproto);
	~svm() = default;

	void    psh(int32_t sym);		// 压栈
	int32_t pop(void);				// 弹栈
	int	 	exe(proto_code pcode);	// 指令执行
	void 	dis(void);				// 打印栈顶元素

  private:
  	friend class proto;
	std::stack<int32_t> call;		// 调用堆栈
	svm_flags 			flag;		// 状态机标志
	proto				*sproto;	// 代码生成
};

/**
 * @brief 
 */
class proto {
  public:
	proto();
	~proto() = default;

	void insert_code(proto_code code);
	void insert_data(proto_data data);

	proto_code next(void);			/* 获取下一个指令 */
	void dump(std::string buffer);	/* 生成字符指令 */

	void do_run(void);				/* 指令执行 */
	void do_jmp(uint64_t pc);		/* 执行跳转 */
	void do_ret(void); 				/* 执行返回 */
	void do_cal(uint64_t pc); 		/* 函数调用 */

  private:
	friend class svm;
	uint32_t pc; 	// 指令计数器
	uint32_t lr;	// 连接计数器
	
	std::vector<proto_code> pcode; 	// 代码段
	std::vector<proto_data> pdata;	// 数据段
	svm 					psvm;   // 虚拟机 
};

} // namespace proto

#endif /* __PROTO_H__ */