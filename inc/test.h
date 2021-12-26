/**
 * @file test.h
 * @brief 自动化测试相关工具
 * @version 0.0.1
 *
 */
#ifndef __TEST_H__
#define __TEST_H__
#include <iostream>

class TestExpr
{
  private:
	std::string Expr;	 // 生成表达式
	int			result;	 // 产生的结果

  public:
	TestExpr()
	{
		Expr   = std::string("1+2");
		result = 3;
	}

	std::string GetExpr(void)
	{
		return this->Expr;
	}

	int GetResult(void)
	{
		return this->result;
	}
};

#endif /* __TEST_H__ */
