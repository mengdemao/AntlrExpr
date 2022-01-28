/**
 * @file grammar.cc
 * @brief Expr语法处理文件
 * @author mengdemao19951021@163.com (mengdemao)
 * @version V0.0.1
 * @date 2022-01-09
 *
 *
 */
#include <config.h>
#include <grammar.h>

/**
 * @brief
 * @param  InputString      My Param doc
 * @return grammar_result
 */
grammar_result grammarMain(std::string InputString)
{
	// 生成解析字符串
	ANTLRInputStream InputStream(InputString);

	// 词法解析
	ExprLexer Lexer(&InputStream);

	// 分割单词
	CommonTokenStream Tokens(&Lexer);

	// 解析语法单元
	ExprParser Parser(&Tokens);

	// 生成语法树
	ParseTree* Tree = Parser.prog();

	// 1. Listener模式解析语法树
	ExprTreeListener Listener;
	ParseTreeWalker	 Walker;
	Walker.walk(&Listener, Tree);

	// 2. Visitor模式校验语法树
	ExprTreeVisitor Visitor;
	Visitor.visit(Tree);

	return GRAMMAR_SUCCESS;
}
