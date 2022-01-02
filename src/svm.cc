/**
 * @file svm.cc
 * @brief 栈式虚拟机实现
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V1.0.0
 * @date 2022-01-02
 *
 *
 */
#include <config.h>
#include <iostream>
#include <option.h>
#include <stack>
#include <string>
#include <syslog.h>
#include <test.h>
#include <svm.h>

namespace svm {
int svm::push(double sym)
{
	call_stacks.push(sym);
}

double svm::pop(void)
{
	double ret = call_stacks.top();
	call_stacks.pop();
	return ret;
}

void svm::dis(void)
{
	double ret = call_stacks.top();
	std::cout << ret << std::endl;
}

int svm::call(svm_ops ops)
{
	double sym1, sym2;
	double res;
	int	   ret;

	sym1 = pop();
	sym2 = pop();

	switch (ops) {
	case ADD:
		res = sym1 + sym2;
		break;

	case SUB:
		res = sym1 - sym2;
		break;

	case MUL:
		res = sym1 * sym2;
		break;

	case DIV:
		res = sym1 / sym2;
		break;

	default:
		return -1;
		break;
	}
	push(res);

	return 0;
}
};	// namespace svm
