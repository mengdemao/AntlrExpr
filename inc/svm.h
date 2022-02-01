/**
 * @file svm.h
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2022-01-23
 *
 * @brief 虚拟机实现
 *
 * @copyright Copyright (c) 2022  mengdemao
 *
 */
#ifndef __SVM_H__
#define __SVM_H__
#include <config.h>
#include <iostream>
#include <option.h>
#include <stack>
#include <string>
#include <syslog.h>
#include <test.h>

namespace svm {

typedef enum {
	OP_NOP,	 //
	OP_MOV,	 //
	OP_LOD,	 //
	OP_STR,	 //
	OP_ADD,	 //
	OP_SUB,	 //
	OP_MUL,	 //
	OP_DIV,	 //
	OP_MOD,	 //
	OP_POW,	 //
	OP_UNM,	 //
	OP_NOT,	 //
	OP_LEN,	 //
	OP_TST,	 //
	OP_CAL,	 //
	OP_JMP,	 //
	OP_RET,	 //
} svm_ops;

class svm
{
  private:
	std::stack<double> call_stack;

  public:
	svm(){

	};

	~svm(){

	};

	void   push(double sym);
	double pop(void);

	int	 call(svm_ops ops);
	void dis(void);
};
}  // namespace svm

#endif /* __SVM_H__ */
