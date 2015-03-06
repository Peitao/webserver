#ifndef WEBSERVER_XUEX0PC0

#define WEBSERVER_XUEX0PC0

#include <signal.h>
#include <evhttp.h>
#include <functional>
#include <string>
#include "threadpool.h"
class WebServer {
 public:
  typedef std::function<void ()> OnDone;
  struct HttpReqResq {
    struct evhttp_request * req;
    struct evbuffer *buf;
    WebServer * webserver;
    OnDone done;
  };
  typedef std::function<void (HttpReqResq *)> OnRequest;
  WebServer(std::string ip , int port, int num, OnRequest cb):_ip(ip),_port(port),_cb(cb),_pool(num) {}
  virtual ~WebServer() {
    //free _base ?
    //free _httpd ?
  }
  bool Init() {
    _base = event_init();
    if (_base == NULL) return false;
    _httpd = evhttp_new(_base);
    if (_httpd == NULL) return false;
    if (evhttp_bind_socket(_httpd, _ip.c_str(), _port) != 0) return false;
    //worker线程返回结果事件
    struct event * send_ev =  event_new(_base, result_queue.fd(),EV_READ|EV_PERSIST, &WebServer::process_request_send, this);
    event_add(send_ev,NULL);
    evhttp_set_gencb(_httpd, &WebServer::process_request_mutil, this);
    signal(SIGPIPE, SIG_IGN);
    _pool.Start();
    return true;
  }
  void Loop() {
    int ret = event_base_dispatch(_base);
    std::cerr << "event_base_dispatch=" << ret << std::endl;
  }
 private:
  //libevent回调
  static void process_request_mutil(struct evhttp_request *req, void *arg);
  //线程池回调
  void done(HttpReqResq * data);
  //libevent回调
  static void process_request_send(evutil_socket_t fd, short what, void *arg);
  struct event_base * _base;
  struct evhttp * _httpd;
  std::string _ip;
  int _port;
  SelectableQueue<HttpReqResq*> result_queue;
  ThreadPool _pool;
  OnRequest _cb;
  void * _data;
};


#endif /* end of include guard: WEBSERVER_XUEX0PC0 */
