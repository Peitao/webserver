#ifndef THREADPOOL_EWF5HPZG

#define THREADPOOL_EWF5HPZG

#include <pthread.h>
#include <iostream>
#include <vector>
#include <functional> 
#include "threadqueue.h"
//线程池： fun(data);
class ThreadPool {
 public:
  typedef std::function<void (void*)> Fun;
  struct Task {
    Task(Fun arg_fun, void * arg_data):fun(arg_fun),data(arg_data){}
    Task(){}
    Fun fun;
    void * data;
  };
  int AddTask(Task t){
    if ( tasks.push(t) != 1 )
      std::cerr << "add err" << std::endl;
  }
  ThreadPool(int num):_num(num){}
  void Start(){
    int err;
    pthread_t tid;
    for (int i = 0; i < _num; i++) {
      err = pthread_create(&tid, NULL, &ThreadPool::_work_run, (void*)this);
      if (err != 0) std::cout << "err ,can't create thread" << std::endl;
      else tids.push_back(tid);
    }
  }
 private:
  static void* _work_run(void * );
  Queue<Task>  tasks;
  std::vector<pthread_t> tids;
  int _num;
};

#endif /* end of include guard: THREADPOOL_EWF5HPZG */
