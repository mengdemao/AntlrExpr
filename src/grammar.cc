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
#include <proto.h>

/**
 * @brief  语法解析
 * @param  input_string     解析字符串
 * @param  ast_root         抽象语法树
 * @return grammar_result 
 */
grammar_result grammar_main(std::string input_string, proto::proto &proto)
{
	// 生成解析字符串
	ANTLRInputStream input_stream(input_string);

	// 词法解析
	ExprLexer lexer(&input_stream);

	// 分割单词
	CommonTokenStream tokens(&lexer);

	// 解析语法单元
	ExprParser parser(&tokens);

	// 生成语法树
	ParseTree* tree = parser.prog();

	// 检查词法分析和语法分析
	if (lexer.getNumberOfSyntaxErrors() > 0 ||
    	parser.getNumberOfSyntaxErrors() > 0) {
		std::cout << "Lexical and/or syntactical errors have been found." << std::endl;
		return GRAMMAR_FAILURE;
	}

	// 1. Listener模式解析语法树
	expr_listener listener;
	ParseTreeWalker	walker;
	walker.walk(&listener, tree);

	// 2. Visitor模式校验语法树
	expr_visitor visitor;
	visitor.visit(tree);

	return GRAMMAR_SUCCESS;
}
