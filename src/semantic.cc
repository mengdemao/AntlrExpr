/**
 * @file semantic.cc
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2022-01-30
 * 
 * @brief 语义分析
 * 
 * @copyright Copyright (c) 2022  mengdemao
 * 
 */
#include <ast.h>
#include <boost/uuid/uuid.hpp>
#include <semantic.h>
#include <string.h>

namespace semantic {

using namespace std;

string attr::get_stat(antlr4::ParserRuleContext* ctx)
{
	return stat_attr.get(ctx);
}

string attr::get_expr(antlr4::ParserRuleContext* ctx)
{
	return expr_attr.get(ctx);
}

void attr::put_stat(antlr4::ParserRuleContext* ctx, const string& stat)
{
	stat_attr.put(ctx, stat);
}

void attr::put_expr(antlr4::ParserRuleContext* ctx, const string& expr)
{
	expr_attr.put(ctx, expr);
}

sym_uuid sym_table::add_var(sym_name name, sym_data data)
{
	sym_item item;

	item.name = name;
	item.uuid = uuid_gen(name);
	item.type = ST_INT;
	item.data = data;
	this->item.push_back(item);

	return item.uuid;
}

void sym_table::del_var(sym_name name)
{

}

void sym_table::del_var(sym_uuid uuid)
{

}

void sym_table::get_var(sym_name name, sym_data &data)
{

}

void sym_table::get_var(sym_uuid name, sym_data &data)
{

}

} // namespace semantic
