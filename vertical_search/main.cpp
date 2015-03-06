#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "webserver.h"
#include "searcher.h"

//一个webserver示例
//HttpReqResq成员：
//  req 是evhttp_request的请求
//  buf 是返回客户端的缓冲区evbuffer

void process_request(WebServer::HttpReqResq * phttp) {

  /*evbuffer_add(phttp->buf, phttp->req->uri, strlen(phttp->req->uri));
  evbuffer_add_printf(phttp->buf, "\n");
  phttp->done();*/
  Searcher * searcher = Searcher::GetSearcher();
  searcher->Search(phttp);
  return;
}
int main(int argc, const char *argv[])
{
  WebServer server("0.0.0.0",10333,5,process_request);
  server.Init();
  server.Loop();
  return 0;
}
