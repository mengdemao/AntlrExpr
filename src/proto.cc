/**
 * @file proto.cc
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.1
 * @date 2022-01-30
 * 
 * @brief 代码生成
 * 
 * @copyright Copyright (c) 2022  mengdemao
 * 
 */
#include <proto.h>

/**
 * @brief Construct a new proto::proto object
 */
proto::proto()
{
	pcode = nullptr;
	pdata = nullptr;

	pc = 0;
	lr = 0;
}

/**
 * @brief 获取下一个指令 
 * @return code 
 */
code proto::next(void)
{
	return pcode[pc++];
}

/**
 * @brief 执行跳转
 * @param  pc 指令计数器
 */
void proto::do_jmp(uint64_t pc)
{
	this->pc = pc;
}

/**
 * @brief 执行返回
 */
void proto::do_ret(void) 
{
	this->pc = this->lr;
}

/**
 * @brief 函数调用
 * @param  pc 指令计数器
 */
void proto::do_cal(uint64_t pc) 
{
	this->pc = pc;
	this->lr = this->pc += 1;
}
