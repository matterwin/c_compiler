#include <iostream>

#include "lexer.h"  

Lexer::Lexer (const std::string& buffer) : input(buffer), errorMsg(ErrorMessages()) {}

void Lexer::printBuffer() const {
  std::cout << "Input buffer: " << input << std::endl;
}
