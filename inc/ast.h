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
#include <test.h>

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
  public:
	ast_base();
	~ast_base();

	virtual void add_root();
	virtual void get_root();

	virtual void addNode();
	virtual void getNode();

	virtual void addLeft();
	virtual void getLeft();

	virtual void addRight();
	virtual void setRight();

  private:
	string	 Name;
	AST_TYPE Type;
	ast_base* Parent;
	ast_base* Left;
	ast_base* Right;
};

class AstNum : ast_base
{
  public:
	double	 getNum(void);
	AST_BOOL setNum(double Num);

  private:
	double Num;
};

class AstSym : ast_base
{
  public:
	AST_SYM	 getSym(void);
	AST_BOOL setSym(AST_SYM Sym);

  private:
	AST_SYM Sym;
};

class AstVar : ast_base
{
  public:
	AST_VAR	 getVar(void);
	AST_BOOL setSym(AST_VAR Var);

  private:
	AST_VAR Var;
};

}  // namespace ast

#endif /* __AST_H__ */
