#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "lexer.h"
#include "token.h"
#include "sym.h"

using namespace std;

void* scanFile(void* arg);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <filename> not provided" << endl;
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    scanFile(argv[i]);   
  }

  // after scanning & generating tokens, pass the tokens to the parser 

  return 0;
}

void* scanFile(void* arg) {
  const char* filename = (const char*)arg;
  ifstream in_file(filename);
  if (!in_file) {
    cout << "Failed to open input file: " << filename << endl;
    return NULL;
  }
  cout << "*** Processing: " << filename << endl;

  string line;
  int line_number = 0;
  while (getline(in_file, line)) {
      line_number++;
      cout << "Line " << line_number << endl;

      for (char c : line) {
        cout << "Character: " << c << endl;
      }
  }

  in_file.close();
  
  // Lexer lexer(buffer);
  // Token tok;
  // do {
  //   tok = lexer.nextToken();
  //   cout << "Token: " << tok.getValue() << endl;
  // } while (tok.getType() != Sym::_EOF);

  return NULL;
}

