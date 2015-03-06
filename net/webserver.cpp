#include "webserver.h"
void WebServer::process_request_mutil(struct evhttp_request *req, void *arg){
  WebServer * p = (WebServer *)arg;
  HttpReqResq * data = new HttpReqResq();
  data->req = req;
  data->buf = evbuffer_new();
  data->webserver = p;
  data->done = std::bind(&WebServer::done,p,data);
  void (*fun)(HttpReqResq *) = *p->_cb.target<void (*)(HttpReqResq *)>();
  ThreadPool::Fun tfun = (void (*)(void *))fun;
  p ->_pool.AddTask(ThreadPool::Task(tfun,data));
}
//把由线程池调用把结果放到result_queue中
void WebServer::done(HttpReqResq * data) {
  data->webserver->result_queue.push(data);
}
void WebServer::process_request_send(evutil_socket_t fd, short what, void *arg) {
  WebServer * p = (WebServer *)arg;
  HttpReqResq * res = NULL;
  p->result_queue.pop(&res);
  evhttp_send_reply(res->req,HTTP_OK,"OK",res->buf);
  if (res->buf) {
    evbuffer_free(res->buf);
  }
  if (res) delete(res);
}
