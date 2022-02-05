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

// 指定操作码的类型为16-->65536
typedef enum : int16_t {
	OP_NOP,	 // 空指令

	// 数据操作指令
	OP_PSH,	 //
	OP_POP,	 //
	OP_LDR,	 //
	OP_STR,	 //

	// 数学计算指令
	OP_ADD,	 //
	OP_SUB,	 //
	OP_MUL,	 //
	OP_DIV,	 //
	OP_MOD,	 //
	OP_POW,	 //
	OP_UNM,	 //

	// 逻辑计算指令
	OP_AND,	 //
	OP_ORR,	 //
	OP_NOT,	 //
	OP_XOR,	 //
	OP_EQU,	 //
	OP_NEQ,	 //

	// 位移指令
	OP_SHL,	 //
	OP_SHR,	 //

	OP_LEN,	 //

	// 跳转指令
	OP_CAL,	 //
	OP_JMP,	 //
	OP_RET,	 //

	OP_OPEN,  // 打开
	OP_READ,  // 读取
	OP_CLOS,  // 关闭
	OP_PRTF,  // 打印
	OP_MALC,  // 内存申请
	OP_FREE,  // 内存释放
	OP_MSET,  // 内存清零
	OP_MCMP,  // 内存拷贝
	OP_EXIT,  // 运行退出
	OP_MARK,  // 操作掩码
} op_code;

typedef int16_t op_cond;
typedef int32_t op_data;

/**
 * @brief 虚拟机指令码
 * 16 : op_code
 * 16 : op_cond
 * 32 : op_data
 */
typedef struct {
	op_code code;
	op_cond cond;
	op_data data;
} proto_code;

/**
 * @brief 栈式虚拟机最核心的数据结构之一
 * 用作高精度数学计算
 */
typedef int64_t proto_value;

/**
 * @brief 全局变量描述
 */
typedef struct {
	std::string name;
	proto_value value;
} proto_data;

/**
 * @brief 虚拟机标志位
 */
typedef struct {
	uint64_t none;
} proto_flags;

/**
 * @brief
 */
class proto
{
  public:
	proto();
	~proto() = default;

	void insert_code(proto_code code); // 添加新的指令
	void insert_data(proto_data data); // 添加新的全局变量

	double execute(void);	// 程序运行

	proto_code next(void); // 获取下一个指令
	proto_code prev(void); //获取上一个指令

	void dump(std::string buffer); /* 生成字符指令 */
	void make(std::string buffer); /* 编译字符指令 */

	void do_jmp(uint64_t pc); /* 执行跳转 */
	void do_cal(uint64_t pc); /* 函数调用 */
	void do_ret(void);		  /* 执行返回 */

	int set_var(int32_t index, proto_value value);	   	// 修改变量值
	int set_var(std::string name, proto_value value);  	// 修改变量值
	int get_var(int32_t index, proto_value& value);		// 获取变量值
	int get_var(std::string name, proto_value& value);	// 获取变量值

  private:
	uint32_t pc;  // 指令计数器
	uint32_t lr;  // 连接计数器

	std::stack<proto_value> call;	 // 调用堆栈
	proto_flags				flag;	 // 状态机标志

	std::vector<proto_code> pcode;	// 代码段
	std::vector<proto_data> pdata;	// 数据段
	
	void dis(void);
	bool exe(proto_code code);
	void psh(proto_value value);
	proto_value pop(void);
};

}  // namespace proto

#endif /* __PROTO_H__ */
