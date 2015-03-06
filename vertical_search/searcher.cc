#include "searcher.h"
#include "query_process.h"
Searcher * Searcher::_searcher = NULL;
pthread_mutex_t Searcher::_mutex;

Searcher * Searcher::GetSearcher() {
  if (_searcher == NULL) {
    pthread_mutex_lock(&_mutex);
    if (_searcher == NULL) {
      _searcher = new Searcher();
    }
    pthread_mutex_unlock(&_mutex);
  }
  else return _searcher;
}

Searcher::Searcher() {
  if (pthread_mutex_init(&_mutex, NULL) != 0) {
    std::cerr << "Fail to init Searcher::_mutex" << std::endl;
  }
}
Searcher::~Searcher() {
  pthread_mutex_destroy(&_mutex);
}

bool Searcher::Search(WebServer::HttpReqResq * phttp) {
  //处理query
  QueryProcess::RawQuery raw_query;
  QueryProcess::ParseFromEvhttpRequest(phttp->req, &raw_query);
  //请求索引
  std::cout << raw_query.query << std::endl;
  //返回结果
  evbuffer_add(phttp->buf, raw_query.query.c_str(), raw_query.query.size());


  phttp->done();
}
