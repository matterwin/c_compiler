#include <iostream>

#include "lexer.h"  
#include "token.h"

Lexer::Lexer (const std::string& buffer) : input(buffer), errorMsg(ErrorMessages()) {}

void Lexer::printBuffer() const {
  std::cout << "Input buffer: " << input << std::endl;
}

Token Lexer::nextToken() {
  if (position >= input.size()) {
    return Token(Sym::_EOF, "yo");
  }

  char ch = input[position++];
  return Token(Sym::CHARACTER, std::string(1, std::string str(1, ch)));
}
