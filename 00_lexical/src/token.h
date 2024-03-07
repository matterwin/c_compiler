#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "sym.h"

class Token {
private:
  Sym type;
  std::string value;

public:
  Token() {}
  Token(Sym sym, std::string val) : type(sym), value(val) {}
  Sym getType() const { return type; } 
  std::string getValue() const { return value; }
};

#endif
