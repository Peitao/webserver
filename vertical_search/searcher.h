#ifndef SEARCHER_ISQ3YGM

#define SEARCHER_ISQ3YGM
#include <pthread.h>
#include "webserver.h"
class Searcher {
 public:
  Searcher();
  ~Searcher();
  bool Search(WebServer::HttpReqResq * phttp);
  static Searcher * GetSearcher();
 private:
  static pthread_mutex_t _mutex;
  static Searcher * _searcher;
};


#endif /* end of include guard: SEARCHER_ISQ3YGM */
