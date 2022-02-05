/**
 * @file proto.cc
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.1
 * @date 2022-01-30
 *
 * @brief 代码生成与虚拟机实现
 *
 * @copyright Copyright (c) 2022  mengdemao
 *
 */
#include <cassert>
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <proto.h>
#include <string>

#include <fmt/core.h>

namespace proto {

/**
 * @brief Construct a new proto::proto object
 */
proto::proto()
{
	static_assert(sizeof(proto_code) == 8);
	static_assert(OP_MARK < 65535);

	pc = 0;
	lr = 0;
}

void proto::insert_code(proto_code code)
{
	this->pcode.push_back(code);
}

void proto::insert_data(proto_data data)
{
	this->pdata.push_back(data);
}

/**
 * @brief 获取下一个指令
 * @return code
 */
proto_code proto::next(void)
{
	return pcode[pc++];
}

/**
 * @brief 导出指令
 * @param  buffer  指令存储缓冲区
 */
void proto::dump(std::string buffer)
{
	for (uint32_t index = 0; index < this->pcode.size(); index++) {
		switch (this->pcode[index].code) {
		case OP_NOP:
			break;

		case OP_PSH:
			break;

		case OP_POP:
			break;

		case OP_LDR:
			break;

		case OP_STR:
			break;

		case OP_ADD:
			break;

		case OP_SUB:
			break;

		case OP_MUL:
			break;

		case OP_DIV:
			break;

		case OP_MOD:
			break;

		case OP_POW:
			break;

		case OP_UNM:
			break;

		case OP_AND:
			break;

		case OP_ORR:
			break;

		case OP_NOT:
			break;

		case OP_XOR:
			break;

		case OP_EQU:
			break;

		case OP_NEQ:
			break;

		case OP_SHL:
			break;

		case OP_SHR:
			break;

		case OP_LEN:
			break;

		case OP_CAL:
			break;

		case OP_JMP:
			break;

		case OP_RET:
			break;

		case OP_OPEN:
			break;

		case OP_READ:
			break;

		case OP_CLOS:
			break;

		case OP_PRTF:
			break;

		case OP_MALC:
			break;

		case OP_FREE:
			break;

		case OP_MSET:
			break;

		case OP_MCMP:
			break;

		case OP_EXIT:
			break;

		default:
			break;
		}
	}
}

/**
 * @brief 编译指令
 * @param  buffer  指令存储缓冲区
 */
void proto::make(std::string buffer)
{
	/* No body */
}

/**
 * @brief
 */
double proto::execute(void)
{
	proto_value tmp_value;
	double ret_value = 0;

	while (this->pc < this->pcode.size()) {
	}

	return ret_value;
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

/**
 * @brief 虚拟机调用堆栈压栈
 * @param  value 需要压入的参数
 */
void proto::psh(proto_value value)
{
	call.push(value);
}

/**
 * @brief 调用堆栈弹栈
 * @return proto_value
 */
proto_value proto::pop(void)
{
	proto_value value = call.top();
	call.pop();
	return value;
}

/**
 * @brief
 */
void proto::dis(void)
{
	proto_value ret = call.top();
	std::cout << ret << std::endl;
}

/**
 * @brief
 * @param  pcode
 * @return int
 */
bool proto::exe(proto_code pcode)
{
	proto_value sym1 = 0, sym2 = 0;
	proto_value res = 0;

	switch (pcode.code) {
	case OP_NOP:
		break;

	case OP_PSH:
		res = pcode.data;
		psh(res);
		break;

	case OP_POP:
		(void)pop();
		break;

	case OP_LDR:
		get_var(pcode.data, res);
		break;

	case OP_STR:
		res = pop();
		set_var(pcode.data, res);
		break;

	case OP_ADD:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 + sym2;
		break;

	case OP_SUB:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 - sym2;
		psh(res);
		break;

	case OP_MUL:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 * sym2;
		psh(res);
		break;

	case OP_DIV:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 / sym2;
		psh(res);
		break;

	case OP_MOD:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 % sym2;
		psh(res);
		break;

	case OP_POW:
		sym1 = pop();
		sym2 = pop();
		res	 = pow(sym1, sym2);
		psh(res);
		break;

	case OP_UNM:
		sym1 = pop();
		res	 = abs(sym2);
		psh(res);
		break;

	case OP_AND:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 & sym2;
		psh(res);
		break;

	case OP_ORR:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 | sym2;
		psh(res);
		break;

	case OP_NOT:
		sym1 = pop();
		res	 = ~sym1;
		psh(res);
		break;

	default:
		return false;
		break;
	}

	return true;
}

/**
 * @brief 设置变量值
 * @param  index 索引
 * @param  value 数值
 */
int proto::set_var(int32_t index, proto_value value)
{
	assert(index >= pdata.size());
	pdata[index].value = value;
	return 0;
}

/**
 * @brief 获取变量值
 * @param  index 	索引
 * @return int64_t  数值
 */
int proto::get_var(int32_t index, proto_value& value)
{
	assert(index >= pdata.size());
	value = pdata[index].value;
	return 0;
}

/**
 * @brief 设置变量值
 * @param  name  变量名
 * @param  value 数值
 */
int proto::set_var(std::string name, proto_value value)
{
	for (int index = 0; index < pdata.size(); index++) {
		if (pdata[index].name == name) {
			pdata[index].value = value;
			return 0;
		}
	}

	return -1;
}

/**
 * @brief 设置变量值
 * @param  name  变量名
 * @param  value 数值
 */
int proto::get_var(std::string name, proto_value& value)
{
	for (int index = 0; index < pdata.size(); index++) {
		if (pdata[index].name == name) {
			value = pdata[index].value;
			return 0;
		}
	}
	return -1;
}

}  // namespace proto
