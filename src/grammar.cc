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
grammar_result grammar_main(std::string InputString)
{
		// 生成解析字符串
	ANTLRInputStream input(InputString);

	// 词法解析
	ExprLexer lexer(&input);

	// 分割单词
	CommonTokenStream tokens(&lexer);

	// 解析语法单元
	ExprParser parser(&tokens);

	// 生成语法树
	ParseTree* tree = parser.prog();

	// 1. Listener模式解析语法树
	ExprTreeListener listener;
	ParseTreeWalker	 walker;
	walker.walk(&listener, tree);

	// 2. Visitor模式校验语法树
	ExprTreeVisitor visitor;
	visitor.visit(tree);

	return GRAMMAR_SUCCESS;
}
