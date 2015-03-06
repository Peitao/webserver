#ifndef QUERY_PROCESS_EG09K9WL

#define QUERY_PROCESS_EG09K9WL
#include <string>
#include "webserver.h"
// 处理query模块
// 主要功能，把原始query进行地域扩展，同义，改写，去杂质词等等。用于后续的检索。
class QueryProcess {
public:
  QueryProcess();
  struct RawQuery {
    std::string query;
    std::string reqStr;
    std::string path;
  };
  static void ParseFromEvhttpRequest (evhttp_request * req,RawQuery * raw);
private:
  
};


#endif /* end of include guard: QUERY_PROCESS_EG09K9WL */
