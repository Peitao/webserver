#include <iostream>
#include "webserver.h"

//一个webserver示例
void process_request(WebServer::HttpReqResq * phttp) {
  evbuffer_add_printf(phttp->buf, "hello world!!");
  phttp->done();
  return;
}
int main(int argc, const char *argv[])
{
  WebServer server("0.0.0.0",12012,5,process_request);
  server.Init();
  server.Loop();
  return 0;
}
