/**
 * @file semantic.h
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2022-02-01
 * 
 * @brief 语义分析
 * 
 * @copyright Copyright (c) 2022  mengdemao
 * 
 */
#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include "antlr4-runtime.h"
#include "tree/ParseTreeProperty.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <proto.h>
#include <stack>
#include <string>
#include <string.h>
#include <vector>

namespace semantic {

using namespace std;
using namespace boost::uuids;

class attr
{
  public:
	attr() = default;
	~attr() = default;

	std::string get_stat(antlr4::ParserRuleContext* ctx);
	std::string	get_expr(antlr4::ParserRuleContext* ctx);

	void put_stat(antlr4::ParserRuleContext* ctx, const std::string& stat);
	void put_expr(antlr4::ParserRuleContext* ctx, const std::string& expr);

  private:
	antlr4::tree::ParseTreeProperty<std::string> stat_attr;
	antlr4::tree::ParseTreeProperty<std::string> expr_attr;
};

enum sym_type {
	ST_INT,		/// 变量
};
typedef int32_t sym_data;
typedef uuid 	sym_uuid;
typedef string 	sym_name;

class sym_table {
private:
	struct sym_item {
		sym_name name;  /// 名字
		sym_uuid uuid;	/// UUID
		sym_type type;  /// 类型
		sym_data data;  /// 数据
	};

	/**
	 * @brief  符号表UUID生成
	 * @param  name 名字
	 * @return uuid UUID
	 */
	name_generator name_gen;
	uuid uuid_gen(string name)
	{
		return name_gen(name);
	}

	vector<sym_item> item; // 符号表项

public:
	sym_table() = default;
	~sym_table() = default;

	sym_uuid add_var(sym_name name, sym_data data);
	void del_var(sym_uuid uuid);
	void del_var(sym_name name);

	void get_var(sym_name name, sym_data &data);
	void get_var(sym_uuid uuid, sym_data &data);
};

class code_generat
{
  private:
  public:
};

} // namespace semantic

#endif /* __SEMANTIC_H__ */
