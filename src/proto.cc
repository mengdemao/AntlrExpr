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

/**
 * @fn void insert_code(proto_code)
 * @brief 插入新的代码
 *
 * @param code
 */
void proto::insert_code(proto_code code)
{
	this->pcode.push_back(code);
}

/**
 * @fn void insert_data(proto_data)
 * @brief 添加新的全局变量
 *
 * @param data
 */
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
void proto::decode(std::string buffer)
{
	/* No body */
}

/**
 * @brief 编译指令
 * @param  buffer  指令存储缓冲区
 */
void proto::encode(std::string buffer)
{
	/* No body */
}

/**
 * @brief 虚拟机执行函数
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
	proto_value sym[PROTO_SYMMAX] = {0};
	proto_value res = 0;

	switch (pcode.code) {
	case OP_NOP:
		res = pop();
		psh(res);
		break;

	case OP_PSH:
		res = pcode.data;
		psh(res);
		break;

	case OP_POP:
		pop();
		break;

	case OP_LDR:
		get_var(pcode.data, res);
		psh(res);
		break;

	case OP_STR:
		res = pop();
		set_var(pcode.data, res);
		break;

	case OP_ADD:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] + sym[1];
		break;

	case OP_SUB:
		sym[0] = pop();
		sym[1] = pop();
		res	= sym[0]- sym[1];
		psh(res);
		break;

	case OP_MUL:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] * sym[1];
		psh(res);
		break;

	case OP_DIV:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] / sym[1];
		psh(res);
		break;

	case OP_MOD:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] % sym[1];
		psh(res);
		break;

	case OP_POW:
		sym[0] = pop();
		sym[1] = pop();
		res	 = pow(sym[0], sym[1]);
		psh(res);
		break;

	case OP_UNM:
		sym[0] = pop();
		res	 = abs(sym[1]);
		psh(res);
		break;

	case OP_AND:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] && sym[1];
		psh(res);
		break;

	case OP_ORR:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] || sym[1];
		psh(res);
		break;

	case OP_NOT:
		sym[0] = pop();
		res	 = !sym[0];
		psh(res);
		break;

	case OP_XOR:
		sym[0] = pop();
		sym[1] = pop();
		res	 = sym[0] ^ sym[1];
		psh(res);
		break;

	case OP_EQU:
		sym[0] = pop();
		sym[1] = pop();
		res = false;
		if (sym[0] == sym[1]) {
			res = true;
		}
		psh(res);
		break;

	case OP_NEQ:
		sym[0] = pop();
		sym[1] = pop();
		res = false;
		if (sym[0] != sym[1]) {
			res = true;
		}
		psh(res);
		break;

	case OP_SHL:
		sym[0] = pop();
		sym[1] = pop();
		res = sym[0] << sym[1];
		psh(res);
		break;

	case OP_SHR:
		sym[0] = pop();
		sym[1] = pop();
		res = sym[0] >> sym[1];
		psh(res);
		break;

	case OP_CAL:
		sym[0] = pop();
		do_cal(sym[0]);
		break;

	case OP_JMP:
		sym[0] = pop();
		do_jmp(sym[0]);
		break;

	case OP_RET:
		do_ret();
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

/**
 * @fn int set_str(int32_t, proto_string)
 * @brief
 *
 * @param index
 * @param value
 * @return
 */
int proto::set_str(int32_t index, proto_string value)
{
	return 0;
}

/**
 * @fn int set_str(std::string, proto_string)
 * @brief
 *
 * @param name
 * @param value
 * @return
 */
int proto::set_str(std::string name, proto_string value)
{
	return 0;
}

/**
 * @fn int get_str(int32_t, proto_string&)
 * @brief
 *
 * @param index
 * @param value
 * @return
 */
int proto::get_str(int32_t index, proto_string& value)
{
	return 0;
}

/**
 * @fn int get_str(std::string, proto_string&)
 * @brief
 *
 * @param name
 * @param value
 * @return
 */
int proto::get_str(std::string name, proto_string& value)
{
	return 0;
}

/**
 * @fn void make_code_psh(int32_t)
 * @brief 压栈代码
 *
 * @param dat
 */
void proto::make_code_psh(int32_t dat)
{
	// TODO: 暂时未实现
}	

/**
 * @fn void make_code_pop(void)
 * @brief 弹栈
 *
 */
void proto::make_code_pop(void)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_ldr(int32_t)
 * @brief
 *
 * @param index
 */
void proto::make_code_ldr(int32_t index)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_str(int32_t)
 * @brief
 *
 * @param index
 */
void proto::make_code_str(int32_t index)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_add(void)
 * @brief
 *
 */
void proto::make_code_add(void)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_sub(void)
 * @brief
 *
 */
void proto::make_code_sub(void)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_mul(void)
 * @brief
 *
 */
void proto::make_code_mul(void)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_div(void)
 * @brief
 *
 */
void proto::make_code_div(void)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_cal(int32_t)
 * @brief
 *
 * @param addr
 */
void proto::make_code_cal(int32_t addr)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_jmp(int32_t)
 * @brief
 *
 * @param addr
 */
void proto::make_code_jmp(int32_t addr)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_ret(void)
 * @brief
 *
 */
void proto::make_code_ret(void)
{
	// TODO: 暂时未实现
}

/**
 * @fn void make_code_ext(void)
 * @brief
 *
 */
void proto::make_code_ext(void)
{
	// TODO: 暂时未实现
}

}  // namespace proto
