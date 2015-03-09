#include <string.h>
#include "query_process.h"
#include "util.h"


QueryProcess::QueryProcess() {

}
void QueryProcess::ParseFromEvhttpRequest (evhttp_request * req,RawQuery * raw) {
  char * decode_uri = evhttp_decode_uri(req->uri);
  (*raw).reqStr = std::string(decode_uri);
  free(decode_uri);
  //  型如 /path?a=123&w=456 
  size_t pos = (*raw).reqStr.find("?");
  if (pos == std::string::npos) return;
  (*raw).path = (*raw).reqStr.substr(0,pos);
  std::map<std::string,std::string> params;
  ParseHttpParms((*raw).reqStr.substr(pos + 1), &params);
  auto it = params.find("q");
  if (it != params.end()) (*raw).query = it->second;
  for ( auto it = params.begin(); it != params.end(); it++ ) {
	  std::cout << it->first << " " << it->second << std::endl;
  }
}
