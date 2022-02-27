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

/**
 * @brief 栈式虚拟机最核心的数据结构之一
 * 用作高精度数学计算
 * FIXME: 使用新定义的数据结构
 */
typedef int64_t proto_value;

/**
 * @fn void proto_value_cast(proto_value, int&)
 * @brief proto_value类型转化为标准类型
 *
 * @param value proto_value
 * @param data 需要转化的数据
 */
void proto_value_cast(proto_value value, int &data);
void proto_value_cast(proto_value value, double &data);
void proto_value_cast(proto_value value, bool &data);

/**
 * @brief 栈式虚拟机最核心的数据结构之一
 * 用作动态字符串设计
 * FIXME: 使用新定义的数据结构
 */
typedef std::string  proto_text;

/**
 * @def PROTO_SYMMAX
 * @brief 参数个数
 *
 */
#define PROTO_SYMMAX   5

// 指定操作码的类型为16-->65536
typedef enum : int16_t {
	OP_NOP,	 // 空指令

	// 数据操作指令
	OP_PSH,	 // 入栈操作
	OP_POP,	 // 出栈操作
	OP_LDR,	 // 加载变量
	OP_STR,	 // 保存变量

	// 数学计算指令
	OP_ADD,	 // 加法
	OP_SUB,	 // 减法
	OP_MUL,	 // 乘法
	OP_DIV,	 // 除法
	OP_MOD,	 // 模除
	OP_POW,	 // 乘方
	OP_UNM,	 // 绝对值

	// 逻辑计算指令
	OP_AND,	 // 与
	OP_ORR,	 // 或
	OP_NOT,	 // 非 
	OP_XOR,	 // 异或
	OP_EQU,	 // 相等
	OP_NEQ,	 // 不等

	// 位移指令
	OP_SHL,	 // 左移
	OP_SHR,	 // 右移

	// 跳转指令
	OP_CAL,	 // 带返回的跳转
	OP_JMP,	 // 不返回的跳转
	OP_RET,	 // 程序执行返回
	OP_EXT,  // 程序运行退出
	OP_LBL,  // 跳转标号

	OP_OPEN,  // 打开
	OP_READ,  // 读取
	OP_CLOS,  // 关闭
	OP_PRTF,  // 打印
	OP_MALC,  // 内存申请
	OP_FREE,  // 内存释放
	OP_MSET,  // 内存清零
	OP_MCMP,  // 内存拷贝
	OP_MARK,  // 操作掩码
} op_code;

typedef int16_t op_cond; // 条件判断
typedef int32_t op_data; // 操作数

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
 * @brief 全局变量描述
 */
typedef struct {
	std::string name;
	proto_value value;
} proto_data;

typedef struct {
	std::string name;
	proto_text text;
} proto_string;

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
  private:
	uint32_t pc;  // 指令计数器
	uint32_t lr;  // 连接计数器

	std::stack<proto_value> call;	 	// 调用堆栈
	proto_flags				flag;	 	// 状态机标志
	proto_value 			swap;		// 数据交换

	std::vector<proto_code> pcode;	 	// 代码段
	std::vector<proto_data> pdata;		// 数据段
	std::vector<proto_string> pstrng;	// 字符串
	
	void dis(void);
	bool exe(proto_code code);
	void psh(proto_value value);
	proto_value pop(void);
 
  public:
	proto();
	~proto() = default;

	/**
	 * @fn void insert_code(proto_code)
	 * @brief 添加新的指令
	 *
	 * @param code
	 */
	void insert_code(proto_code code);

	/**
	 * @fn void insert_data(proto_data)
	 * @brief 添加新的全局变量
	 *
	 * @param data
	 */
	void insert_data(proto_data data);

	/**
	 * @fn void make_code_psh(int32_t)
	 * @brief
	 *
	 * @param dat
	 */
	void make_code_psh(int32_t dat);

	/**
	 * @fn void make_code_pop(void)
	 * @brief
	 *
	 */
	void make_code_pop(void);

	/**
	 * @fn void make_code_ldr(int32_t)
	 * @brief
	 *
	 * @param index
	 */
	void make_code_ldr(int32_t index);

	/**
	 * @fn void make_code_str(int32_t)
	 * @brief
	 *
	 * @param index
	 */
	void make_code_str(int32_t index);

	/**
	 * @fn void make_code_add(void)
	 * @brief
	 *
	 */
	void make_code_add(void);

	/**
	 * @fn void make_code_sub(void)
	 * @brief
	 *
	 */
	void make_code_sub(void);

	/**
	 * @fn void make_code_mul(void)
	 * @brief
	 *
	 */
	void make_code_mul(void);

	/**
	 * @fn void make_code_div(void)
	 * @brief
	 *
	 */
	void make_code_div(void);

	/**
	 * @fn void make_code_mod(void)
	 * @brief
	 *
	 */
	void make_code_mod(void);

	/**
	 * @fn void make_code_cal(int32_t)
	 * @brief
	 *
	 * @param addr
	 */
	void make_code_cal(int32_t addr);

	/**
	 * @fn void make_code_jmp(int32_t)
	 * @brief
	 *
	 * @param addr
	 */
	void make_code_jmp(int32_t addr);

	/**
	 * @fn void make_code_lbl(int32_t)
	 * @brief
	 *
	 * @param addr
	 */
	void make_code_lbl(int32_t addr);

	/**
	 * @fn void make_code_ret(void)
	 * @brief
	 *
	 */
	void make_code_ret(void);

	/**
	 * @fn void make_code_ext(void)
	 * @brief
	 *
	 */
	void make_code_ext(void);

	/**
     * @fn void optimize(void)
	 * @brief 优化相关指令
	 *
	 */
	void optimize(void);

	/**
	 * @fn double execute(void)
	 * @brief 程序运行
	 *
	 * @return
	 */
	proto_value execute(void);

	proto_code next(void); // 获取下一个指令
	proto_code prev(void); // 获取上一个指令

	void encode(std::string buffer); /* 生成字符指令 */
	void decode(std::string buffer); /* 编译字符指令 */

	void do_jmp(uint64_t pc); /* 执行跳转 */
	void do_cal(uint64_t pc); /* 函数调用 */
	void do_ret(void);		  /* 执行返回 */

	int set_var(int32_t index, proto_value value);	   	// 修改变量值
	int set_var(std::string name, proto_value value);  	// 修改变量值
	int get_var(int32_t index, proto_value& value);		// 获取变量值
	int get_var(std::string name, proto_value& value);	// 获取变量值

	int set_str(int32_t index, proto_string value);	   	// 修改字符串
	int set_str(std::string name, proto_string value);  // 修改字符串
	int get_str(int32_t index, proto_string& value);	// 获取字符串
	int get_str(std::string name, proto_string& value);	// 获取字符串
};

}  // namespace proto

#endif /* __PROTO_H__ */
