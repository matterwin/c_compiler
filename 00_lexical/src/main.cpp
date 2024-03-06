#include <iostream>
#include <fstream>
#include <cstring>
#include <pthread.h>
#include <vector>

#include "lexer.h"

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

  Lexer lexer("testing");
  lexer.printBuffer();

  fs.close();
  return NULL;

  // parallelize the file into chunks
  // if there are any mistakes/errors thrown, 2 things could have happenend: (both can happen)
  // 1. user error 
  // 2. token splitting error from chunk cutoffs

  // if no errors are thrown, then the code looks lexically correct.

  // if errors were thrown, check first if the token's were split off
  // (idea to figure this out is throw an 'unfinished token error' once the curr char is near the end of the chunk.
  // check with the next thread's chunk and if an that same error was thrown but given the error was thrown near the beginning
  // of the chunk, then possibly figure out how to combine the two. (like keep track of the chars in the error msg and combine the 2 error
  // msgs and their values to mold the new token)
  //
  // if a different type of error was thrown, then we can guess the user had a wrong lexical syntax.
  // ) 
  // since both can happen, we need to always check 
  //
  // somehow if a token was split, then we need to place that token in the proper order of when it falls into the source code.
  // 
  // 1 approach: FIFO queue (thread safe)
  // all tokens from a chunk are pushed to this queue if error free.
  // if the older chunks have not finished yet, due to error checking/token splitting, then the new/already done chunks would
  // have to wait for the elders to sort the shit out (potential bottleneck)
  //
  // 2 approach: fixed array of chunk tokens (thread safe)
  // source code per file will have an array size # of of chunks
  // a thread will push its tokens at once to their specific indexed chunk in the array whenever they are completely done and no errors
  // if a thread finds a 'token split' error, then before placing it, it needs to check for its sister chunk to catch its 'token split',
  // so, if a thread catches such error, then it needs to check the chunk before or after it (depending on when the token split was found), 
  //
  // fusing those tokens are a whole other issue, but once u fuse the tokens, then place those token chunks into their respt index
  //
  // now deciding when to push the tokens to the parsers is only topic of discussion:
  // do we want to wait for all tokens to get pushed to the array?
  // do we want to push only token chunks starting from the 0 index to the next available/error-free token chunks?
  //  - with that entails marking a index in an error state, thus blocking the push of other token chunks
  //
  // the important thing for the parser is that the tokens need to be in order, which is obvious but just fyi
  //
  // 'token split' error happens only near the end of beginning of the chunk, since that is where a split would occur

