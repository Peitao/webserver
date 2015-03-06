#include <string.h>
#include "query_process.h"
#include "util.h"


QueryProcess::QueryProcess() {

}
void QueryProcess::ParseFromEvhttpRequest (evhttp_request * req,RawQuery * raw) {
  (*raw).reqStr = std::string(req->uri,req->uri + strlen(req->uri));
  //  型如 /path?a=123&w=456 
  size_t pos = (*raw).reqStr.find("?");
  if (pos == std::string::npos) return;
  (*raw).path = (*raw).reqStr.substr(0,pos);
  std::map<std::string,std::string> params;
  ParseHttpParms((*raw).reqStr.substr(pos), &params);
  auto it = params.find("q");
  if (it != params.end()) (*raw).query = it->second;
}
