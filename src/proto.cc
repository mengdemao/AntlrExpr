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
#include <cstdint>
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
	pcode = nullptr;
	pdata = nullptr;

	pc = 0;
	lr = 0;
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
	for (uint32_t index = 0; index < this->ps; index++) {
		switch (this->pcode[index].code) {
		case OP_NOP:
			break;

		case OP_MOV:
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
 * @brief Construct a new svm::svm object
 */
svm::svm()
{
	/* No Body */
}

/**
 * @brief
 * @param  sym
 */
void svm::psh(int32_t sym)
{
	call_stack.push(sym);
}

/**
 * @brief
 * @return int32_t
 */
int32_t svm::pop(void)
{
	int32_t ret = call_stack.top();
	call_stack.pop();
	return ret;
}

/**
 * @brief
 */
void svm::disp(void)
{
	double ret = call_stack.top();
	std::cout << ret << std::endl;
}

/**
 * @brief
 * @param  pcode
 * @return int
 */
int svm::call(proto_code pcode)
{
	int32_t sym1 = 0, sym2 = 0;
	int32_t res = 0;

	switch (pcode.code) {
	case OP_NOP:
		break;

	case OP_MOV:
		res = pcode.data;
		psh(res);
		break;

	case OP_LDR:
		break;

	case OP_STR:
		break;

	case OP_ADD:
		sym1 = pop();
		sym2 = pop();
		res	 = sym1 + sym2;
		psh(res);
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

	default:
		return -1;
		break;
	}

	return 0;
}
}  // namespace proto