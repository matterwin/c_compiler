#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

struct ErrorMessages {
  std::vector<std::string> messages = {
    "Error: Unmatched end-of-comment punctuation.",
    "Error: Unmatched start-of-comment punctuation.",
    "Error: Unclosed string.",
    "Error: Illegal Character."
  };
}; 

class Lexer {
private:
  std::string input;
  const ErrorMessages errorMsg;

public:
  Lexer (const std::string& buffer);

  void printBuffer() const;
};

#endif
