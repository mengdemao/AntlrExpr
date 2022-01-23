/**
 * @file svm.cc
 * @brief 虚拟机实现
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
#include <svm.h>
#include <syslog.h>
#include <test.h>

namespace svm {
void svm::push(double sym)
{
	call_stack.push(sym);
}

double svm::pop(void)
{
	double Ret = call_stack.top();
	call_stack.pop();
	return Ret;
}

void svm::dis(void)
{
	double ret = call_stack.top();
	std::cout << ret << std::endl;
}

int svm::call(svm_ops ops)
{
	double sym1, sym2;
	double res;

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
}  // namespace svm
