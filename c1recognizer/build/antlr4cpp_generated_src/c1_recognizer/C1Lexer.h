
// Generated from /home/crazy/3-compilerh/c1recognizer/grammar/C1Lexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"


namespace c1_recognizer {


class  C1Lexer : public antlr4::Lexer {
public:
  enum {
    Comma = 1, SemiColon = 2, Assign = 3, LeftBracket = 4, RightBracket = 5, 
    LeftBrace = 6, RightBrace = 7, LeftParen = 8, RightParen = 9, If = 10, 
    Else = 11, While = 12, Const = 13, Equal = 14, NonEqual = 15, Less = 16, 
    Greater = 17, LessEqual = 18, GreaterEqual = 19, Plus = 20, Minus = 21, 
    Multiply = 22, Divide = 23, Modulo = 24, Int = 25, Float = 26, Void = 27, 
    Identifier = 28, IntConst = 29, FloatConst = 30, WhiteSpace = 31, Comment = 32
  };

  C1Lexer(antlr4::CharStream *input);
  ~C1Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace c1_recognizer
