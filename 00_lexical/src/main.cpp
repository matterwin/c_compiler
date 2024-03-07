#include <iostream>
#include <fstream>
#include <cstring>
#include <pthread.h>
#include <vector>

#include "lexer.h"
#include "token.h"
#include "sym.h"

void* scanFile(void* arg);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename> not provided" << std::endl;
    return 1;
  }

  std::vector<pthread_t> threads;
  for (int i = 1; i < argc; i++) {
    pthread_t tid;
    if (pthread_create(&tid, NULL, scanFile, (void*)argv[i]) != 0) {
      std::cerr << "Error creating thread" << std::endl;
      return 1;
    }
    threads.push_back(tid);
  }

  for (pthread_t tid : threads) {
    if (pthread_join(tid, NULL) != 0) {
      std::cerr << "Error joining thread" << std::endl;
      return 1;
    }
  }

  return 0;
}

void* scanFile(void* arg) {
  const char* filename = (const char*)arg;
  std::ifstream in_file(filename);
  if (!in_file) {
    std::cout << "Failed to open input file." << std::endl;
    return NULL;
  }

  std::string buffer((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());

  Lexer lexer(buffer);
  Token tok;
  do {
    tok = lexer.nextToken();
    std::cout << "Token: " << tok.getValue() << std::endl;
  } while (tok.getType() != Sym::_EOF);

  return NULL;
}

