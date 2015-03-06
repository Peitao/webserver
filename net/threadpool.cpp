#include <iostream>
#include <stdlib.h>
#include "threadpool.h"

void* ThreadPool::_work_run(void * f) {
  ThreadPool * pool = (ThreadPool *)f;
  Task t;
  while (true) {
    if ( pool->tasks.pop(&t) == 1 ) {
        (t.fun)(t.data);
    } else {
      std::cerr << "pop -1" << std::endl;
    }
  }
  std::cerr << ".......child die" << std::endl;
  exit(0);
  return NULL;
}
