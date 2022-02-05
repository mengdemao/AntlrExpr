/**
 * @file ast.h
 * @brief AST实现
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V1.0.0
 * @date 2022-01-02
 *
 *
 */
#ifndef __AST_H__
#define __AST_H__
#include <config.h>
#include <iostream>
#include <option.h>
#include <stack>
#include <string>
#include <syslog.h>

namespace ast {
using namespace std;
typedef bool AST_BOOL;

typedef enum {
	TYPE_NIL,
	TYPE_NUM,
	TYPE_SYM,
	TYPE_VAR,
} AST_TYPE;

typedef enum {
	SYM_NIL,
	SYM_ADD,
	SYM_SUB,
	SYM_MUL,
	SYM_DIV,
	SYM_MOD,
	SYM_POW,
} AST_SYM;

typedef struct {

} AST_VAR;

class ast_base
{
  private:
	string	 name;
	AST_TYPE type;
	ast_base* parent;
	ast_base* left;
	ast_base* right;

  public:
	ast_base()
	{
		/* No Body */
	}

	~ast_base()
	{
		/* No Body */
	}

	virtual void add_root();
	virtual void get_root();

	virtual void add_node();
	virtual void get_node();

	virtual void add_left();
	virtual void get_left();

	virtual void add_right();
	virtual void set_right();
};

class ast_num : ast_base
{
  public:
	double	 get_num(void);
	AST_BOOL set_num(double num);

  private:
	double num;
};

class ast_sym : ast_base
{
  public:
	AST_SYM	 get_sym(void);
	AST_BOOL set_sym(AST_SYM sym);

  private:
	AST_SYM sym;
};

class ast_var : ast_base
{
  public:
	AST_VAR	 get_var(void);
	AST_BOOL set_var(AST_VAR var);

  private:
	AST_VAR var;
};

}  // namespace ast

#endif /* __AST_H__ */
