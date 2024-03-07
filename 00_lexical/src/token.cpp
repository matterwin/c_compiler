#include "token.h"

Token::Token() {}

Token::Token(Sym sym, std::string val) : type(sym), value(val) {}

Sym Token::getType() const {
    return type;
}

std::string Token::getValue() const {
    return value;
}

