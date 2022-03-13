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
#include <logger.h>
#include <proto.h>

using namespace antlrcpp;
using namespace antlr4;

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
	expr_listener listener(&proto);
	ParseTreeWalker	walker;
	walker.walk(&listener, tree);

	// 2. Visitor模式校验语法树
	expr_visitor visitor;
	visitor.visit(tree);

	return GRAMMAR_SUCCESS;
}

void expr_listener::enterProg(ExprParser::ProgContext* ctx)
{
}
void expr_listener::exitProg(ExprParser::ProgContext* ctx)
{
	proto_vm->make_code_pop();
}

/**
 * @fn void enterPrintExpr(ExprParser::PrintExprContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterPrintExpr(ExprParser::PrintExprContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void exitPrintExpr(ExprParser::PrintExprContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitPrintExpr(ExprParser::PrintExprContext* ctx)
{
}

/**
 * @fn void enterAssign(ExprParser::AssignContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterAssign(ExprParser::AssignContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void exitAssign(ExprParser::AssignContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitAssign(ExprParser::AssignContext* ctx)
{
	log_trace("{}\r\n", ctx->ID()->getText());
}

/**
 * @fn void enterBlank(ExprParser::BlankContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterBlank(ExprParser::BlankContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void exitBlank(ExprParser::BlankContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitBlank(ExprParser::BlankContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void enterParens(ExprParser::ParensContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterParens(ExprParser::ParensContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void exitParens(ExprParser::ParensContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitParens(ExprParser::ParensContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void enterMulDiv(ExprParser::MulDivContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterMulDiv(ExprParser::MulDivContext* ctx)
{
	// log_trace("{}", ctx->op->getText());
}

/**
 * @fn void exitMulDiv(ExprParser::MulDivContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitMulDiv(ExprParser::MulDivContext* ctx)
{
	// log_trace("{}", ctx->op->getText());
	if (ctx->op->getType() == ExprParser::MUL) {
		proto_vm->make_code_mul();
	} else if (ctx->op->getType() == ExprParser::DIV) {
		proto_vm->make_code_div();
	} else if (ctx->op->getType() == ExprParser::MOD) {
		proto_vm->make_code_mod();
	} else {
		log_trace("Unknow op {}", ctx->op->getText());
	}
}

/**
 * @fn void enterAddSub(ExprParser::AddSubContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterAddSub(ExprParser::AddSubContext* ctx)
{
	// log_trace("{}", ctx->op->getText());
}

/**
 * @fn void exitAddSub(ExprParser::AddSubContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitAddSub(ExprParser::AddSubContext* ctx)
{
	if (ctx->op->getType() == ExprParser::ADD) {
		proto_vm->make_code_add();
	} else if (ctx->op->getType() == ExprParser::SUB) {
		proto_vm->make_code_sub();
	} else {
		log_trace("Unknow op {}", ctx->op->getText());
	}
}

/**
 * @fn void enterId(ExprParser::IdContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterId(ExprParser::IdContext* ctx)
{
	log_trace("{}", ctx->getText());
}

/**
 * @fn void exitId(ExprParser::IdContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitId(ExprParser::IdContext* ctx)
{
	log_trace("{}", ctx->getText());
}

/**
 * @fn void enterInt(ExprParser::IntContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterInt(ExprParser::IntContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void exitInt(ExprParser::IntContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitInt(ExprParser::IntContext* ctx)
{
	// log_trace("{}", ctx->INT()->getText());
	proto_vm->make_code_psh(stoi(ctx->INT()->getText()));
}

/**
 * @fn void enterEveryRule(antlr4::ParserRuleContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::enterEveryRule(antlr4::ParserRuleContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void exitEveryRule(antlr4::ParserRuleContext*)
 * @brief
 *
 * @param ctx
 */
void expr_listener::exitEveryRule(antlr4::ParserRuleContext* ctx)
{
	// log_trace("{}", ctx->getText());
}

/**
 * @fn void visitTerminal(antlr4::tree::TerminalNode*)
 * @brief
 *
 * @param node
 */
void expr_listener::visitTerminal(antlr4::tree::TerminalNode* node)
{
	// log_trace("{}", node->getText());
}

/**
 * @fn void visitErrorNode(antlr4::tree::ErrorNode*)
 * @brief
 *
 * @param node
 */
void expr_listener::visitErrorNode(antlr4::tree::ErrorNode* node)
{
	// log_trace("{}", node->getText());
}

/**
 * @fn antlrcpp::Any visitProg(ExprParser::ProgContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitProg(ExprParser::ProgContext* context)
{
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitPrintExpr(ExprParser::PrintExprContext* context)
{
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitAssign(ExprParser::AssignContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitAssign(ExprParser::AssignContext* context)
{
	return visitChildren(context);
}

/**
 * @fn expr_visitor::antlrcpp::Any visitBlank(ExprParser::BlankContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitBlank(ExprParser::BlankContext* context)
{
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitParens(ExprParser::ParensContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitParens(ExprParser::ParensContext* context)
{
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitMulDiv(ExprParser::MulDivContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitMulDiv(ExprParser::MulDivContext* context)
{
	std::string text = context->op->getText();
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitAddSub(ExprParser::AddSubContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitAddSub(ExprParser::AddSubContext* context)
{
	std::string text = context->op->getText();
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitId(ExprParser::IdContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitId(ExprParser::IdContext* context)
{
	std::string text = context->ID()->getText();
	return visitChildren(context);
}

/**
 * @fn antlrcpp::Any visitInt(ExprParser::IntContext*)
 * @brief
 *
 * @param context
 * @return
 */
antlrcpp::Any expr_visitor::visitInt(ExprParser::IntContext* context)
{
	std::string text = context->INT()->getText();
	return visitChildren(context);
}
