#include <iostream>
#include <fstream>
#include <cstring>
#include <pthread.h>
#include <vector>

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
  std::fstream fs{filename};
  if (!fs.is_open()) {
    std::cerr << "Error: Unable to open file" << std::endl;
    return NULL;
  }

  char c;
  while (fs.get(c)) {
    std::cout << c;
  }

  fs.close();
  return NULL;
}

