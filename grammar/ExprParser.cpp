
// Generated from /home/mengdemao/work/AntlrExpr/Expr.g4 by ANTLR 4.9.2


#include "ExprListener.h"
#include "ExprVisitor.h"

#include "ExprParser.h"


using namespace antlrcpp;
using namespace antlr4;

ExprParser::ExprParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ExprParser::~ExprParser() {
  delete _interpreter;
}

std::string ExprParser::getGrammarFileName() const {
  return "Expr.g4";
}

const std::vector<std::string>& ExprParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ExprParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

ExprParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExprParser::StatContext *> ExprParser::ProgContext::stat() {
  return getRuleContexts<ExprParser::StatContext>();
}

ExprParser::StatContext* ExprParser::ProgContext::stat(size_t i) {
  return getRuleContext<ExprParser::StatContext>(i);
}


size_t ExprParser::ProgContext::getRuleIndex() const {
  return ExprParser::RuleProg;
}

void ExprParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void ExprParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}


antlrcpp::Any ExprParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ProgContext* ExprParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, ExprParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(7); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(6);
      stat();
      setState(9); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExprParser::T__0)
      | (1ULL << ExprParser::ID)
      | (1ULL << ExprParser::INT)
      | (1ULL << ExprParser::NEWLINE))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

ExprParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::StatContext::getRuleIndex() const {
  return ExprParser::RuleStat;
}

void ExprParser::StatContext::copyFrom(StatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BlankContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::BlankContext::NEWLINE() {
  return getToken(ExprParser::NEWLINE, 0);
}

ExprParser::BlankContext::BlankContext(StatContext *ctx) { copyFrom(ctx); }

void ExprParser::BlankContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlank(this);
}
void ExprParser::BlankContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlank(this);
}

antlrcpp::Any ExprParser::BlankContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitBlank(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrintExprContext ------------------------------------------------------------------

ExprParser::ExprContext* ExprParser::PrintExprContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

tree::TerminalNode* ExprParser::PrintExprContext::NEWLINE() {
  return getToken(ExprParser::NEWLINE, 0);
}

ExprParser::PrintExprContext::PrintExprContext(StatContext *ctx) { copyFrom(ctx); }

void ExprParser::PrintExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrintExpr(this);
}
void ExprParser::PrintExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrintExpr(this);
}

antlrcpp::Any ExprParser::PrintExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitPrintExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::AssignContext::ID() {
  return getToken(ExprParser::ID, 0);
}

tree::TerminalNode* ExprParser::AssignContext::ASG() {
  return getToken(ExprParser::ASG, 0);
}

ExprParser::ExprContext* ExprParser::AssignContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

tree::TerminalNode* ExprParser::AssignContext::NEWLINE() {
  return getToken(ExprParser::NEWLINE, 0);
}

ExprParser::AssignContext::AssignContext(StatContext *ctx) { copyFrom(ctx); }

void ExprParser::AssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign(this);
}
void ExprParser::AssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign(this);
}

antlrcpp::Any ExprParser::AssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitAssign(this);
  else
    return visitor->visitChildren(this);
}
ExprParser::StatContext* ExprParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 2, ExprParser::RuleStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(20);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<ExprParser::PrintExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(11);
      expr(0);
      setState(12);
      match(ExprParser::NEWLINE);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<ExprParser::AssignContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(14);
      match(ExprParser::ID);
      setState(15);
      match(ExprParser::ASG);
      setState(16);
      expr(0);
      setState(17);
      match(ExprParser::NEWLINE);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatContext *>(_tracker.createInstance<ExprParser::BlankContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(19);
      match(ExprParser::NEWLINE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ExprParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExprParser::ExprContext::getRuleIndex() const {
  return ExprParser::RuleExpr;
}

void ExprParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParensContext ------------------------------------------------------------------

ExprParser::ExprContext* ExprParser::ParensContext::expr() {
  return getRuleContext<ExprParser::ExprContext>(0);
}

ExprParser::ParensContext::ParensContext(ExprContext *ctx) { copyFrom(ctx); }

void ExprParser::ParensContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParens(this);
}
void ExprParser::ParensContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParens(this);
}

antlrcpp::Any ExprParser::ParensContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitParens(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivContext ------------------------------------------------------------------

std::vector<ExprParser::ExprContext *> ExprParser::MulDivContext::expr() {
  return getRuleContexts<ExprParser::ExprContext>();
}

ExprParser::ExprContext* ExprParser::MulDivContext::expr(size_t i) {
  return getRuleContext<ExprParser::ExprContext>(i);
}

tree::TerminalNode* ExprParser::MulDivContext::MUL() {
  return getToken(ExprParser::MUL, 0);
}

tree::TerminalNode* ExprParser::MulDivContext::DIV() {
  return getToken(ExprParser::DIV, 0);
}

tree::TerminalNode* ExprParser::MulDivContext::MOD() {
  return getToken(ExprParser::MOD, 0);
}

ExprParser::MulDivContext::MulDivContext(ExprContext *ctx) { copyFrom(ctx); }

void ExprParser::MulDivContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulDiv(this);
}
void ExprParser::MulDivContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulDiv(this);
}

antlrcpp::Any ExprParser::MulDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitMulDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubContext ------------------------------------------------------------------

std::vector<ExprParser::ExprContext *> ExprParser::AddSubContext::expr() {
  return getRuleContexts<ExprParser::ExprContext>();
}

ExprParser::ExprContext* ExprParser::AddSubContext::expr(size_t i) {
  return getRuleContext<ExprParser::ExprContext>(i);
}

tree::TerminalNode* ExprParser::AddSubContext::ADD() {
  return getToken(ExprParser::ADD, 0);
}

tree::TerminalNode* ExprParser::AddSubContext::SUB() {
  return getToken(ExprParser::SUB, 0);
}

ExprParser::AddSubContext::AddSubContext(ExprContext *ctx) { copyFrom(ctx); }

void ExprParser::AddSubContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddSub(this);
}
void ExprParser::AddSubContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddSub(this);
}

antlrcpp::Any ExprParser::AddSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitAddSub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::IdContext::ID() {
  return getToken(ExprParser::ID, 0);
}

ExprParser::IdContext::IdContext(ExprContext *ctx) { copyFrom(ctx); }

void ExprParser::IdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterId(this);
}
void ExprParser::IdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitId(this);
}

antlrcpp::Any ExprParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* ExprParser::IntContext::INT() {
  return getToken(ExprParser::INT, 0);
}

ExprParser::IntContext::IntContext(ExprContext *ctx) { copyFrom(ctx); }

void ExprParser::IntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt(this);
}
void ExprParser::IntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExprListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt(this);
}

antlrcpp::Any ExprParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExprVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}

ExprParser::ExprContext* ExprParser::expr() {
   return expr(0);
}

ExprParser::ExprContext* ExprParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExprParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ExprParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, ExprParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(29);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExprParser::INT: {
        _localctx = _tracker.createInstance<IntContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(23);
        match(ExprParser::INT);
        break;
      }

      case ExprParser::ID: {
        _localctx = _tracker.createInstance<IdContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(24);
        match(ExprParser::ID);
        break;
      }

      case ExprParser::T__0: {
        _localctx = _tracker.createInstance<ParensContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(25);
        match(ExprParser::T__0);
        setState(26);
        expr(0);
        setState(27);
        match(ExprParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(39);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(37);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(31);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(32);
          dynamic_cast<MulDivContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << ExprParser::MOD)
            | (1ULL << ExprParser::MUL)
            | (1ULL << ExprParser::DIV))) != 0))) {
            dynamic_cast<MulDivContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(33);
          expr(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(34);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(35);
          dynamic_cast<AddSubContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == ExprParser::ADD

          || _la == ExprParser::SUB)) {
            dynamic_cast<AddSubContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(36);
          expr(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(41);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool ExprParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ExprParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ExprParser::_decisionToDFA;
atn::PredictionContextCache ExprParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ExprParser::_atn;
std::vector<uint16_t> ExprParser::_serializedATN;

std::vector<std::string> ExprParser::_ruleNames = {
  "prog", "stat", "expr"
};

std::vector<std::string> ExprParser::_literalNames = {
  "", "'('", "')'", "'='", "'%'", "'*'", "'/'", "'+'", "'-'"
};

std::vector<std::string> ExprParser::_symbolicNames = {
  "", "", "", "ASG", "MOD", "MUL", "DIV", "ADD", "SUB", "ID", "INT", "NEWLINE", 
  "WS"
};

dfa::Vocabulary ExprParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ExprParser::_tokenNames;

ExprParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0xe, 0x2d, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x3, 0x2, 0x6, 0x2, 0xa, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 
       0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x17, 0xa, 0x3, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
       0x4, 0x20, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x7, 0x4, 0x28, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2b, 
       0xb, 0x4, 0x3, 0x4, 0x2, 0x3, 0x6, 0x5, 0x2, 0x4, 0x6, 0x2, 0x4, 
       0x3, 0x2, 0x6, 0x8, 0x3, 0x2, 0x9, 0xa, 0x2, 0x30, 0x2, 0x9, 0x3, 
       0x2, 0x2, 0x2, 0x4, 0x16, 0x3, 0x2, 0x2, 0x2, 0x6, 0x1f, 0x3, 0x2, 
       0x2, 0x2, 0x8, 0xa, 0x5, 0x4, 0x3, 0x2, 0x9, 0x8, 0x3, 0x2, 0x2, 
       0x2, 0xa, 0xb, 0x3, 0x2, 0x2, 0x2, 0xb, 0x9, 0x3, 0x2, 0x2, 0x2, 
       0xb, 0xc, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3, 0x3, 0x2, 0x2, 0x2, 0xd, 
       0xe, 0x5, 0x6, 0x4, 0x2, 0xe, 0xf, 0x7, 0xd, 0x2, 0x2, 0xf, 0x17, 
       0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 0x7, 0xb, 0x2, 0x2, 0x11, 0x12, 0x7, 
       0x5, 0x2, 0x2, 0x12, 0x13, 0x5, 0x6, 0x4, 0x2, 0x13, 0x14, 0x7, 0xd, 
       0x2, 0x2, 0x14, 0x17, 0x3, 0x2, 0x2, 0x2, 0x15, 0x17, 0x7, 0xd, 0x2, 
       0x2, 0x16, 0xd, 0x3, 0x2, 0x2, 0x2, 0x16, 0x10, 0x3, 0x2, 0x2, 0x2, 
       0x16, 0x15, 0x3, 0x2, 0x2, 0x2, 0x17, 0x5, 0x3, 0x2, 0x2, 0x2, 0x18, 
       0x19, 0x8, 0x4, 0x1, 0x2, 0x19, 0x20, 0x7, 0xc, 0x2, 0x2, 0x1a, 0x20, 
       0x7, 0xb, 0x2, 0x2, 0x1b, 0x1c, 0x7, 0x3, 0x2, 0x2, 0x1c, 0x1d, 0x5, 
       0x6, 0x4, 0x2, 0x1d, 0x1e, 0x7, 0x4, 0x2, 0x2, 0x1e, 0x20, 0x3, 0x2, 
       0x2, 0x2, 0x1f, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1a, 0x3, 0x2, 0x2, 
       0x2, 0x1f, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x20, 0x29, 0x3, 0x2, 0x2, 0x2, 
       0x21, 0x22, 0xc, 0x7, 0x2, 0x2, 0x22, 0x23, 0x9, 0x2, 0x2, 0x2, 0x23, 
       0x28, 0x5, 0x6, 0x4, 0x8, 0x24, 0x25, 0xc, 0x6, 0x2, 0x2, 0x25, 0x26, 
       0x9, 0x3, 0x2, 0x2, 0x26, 0x28, 0x5, 0x6, 0x4, 0x7, 0x27, 0x21, 0x3, 
       0x2, 0x2, 0x2, 0x27, 0x24, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2b, 0x3, 0x2, 
       0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 
       0x2, 0x2a, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 
       0x7, 0xb, 0x16, 0x1f, 0x27, 0x29, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ExprParser::Initializer ExprParser::_init;
