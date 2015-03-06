#include <iostream>
#include <errno.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <event2/event-config.h>
#include <unistd.h>
#include "webserver.h"
//几个功能:
//  1. 发送文件
//  2. 执行python脚本, 传递get参数和cookie和post参数
bool RunCmdAndGetResult(const std::string & cmd, std::string *result) {
  FILE * out = NULL;
  char BUFF[5*1024];
  out = popen(cmd.c_str(), "r");
  if (out == NULL) {
    return false;
  }
  while ( fgets(BUFF, sizeof(BUFF), out) ) {
    *result += BUFF;
  }
  pclose(out);
  return true;
}

const char * endheader = "\nendheader\n";
const char * web_dir_prefix = "../website";
void parse_args_from_evhttp_request(struct evhttp_request *req) {
}
unsigned long get_file_size(const char *path) {
  unsigned long filesize = -1;
  struct stat statbuff;
  if(stat(path, &statbuff) < 0){
    return filesize;
  } else {
    filesize = statbuff.st_size;
    return filesize;
  }
}
std::string get_file_content_type(std::string path) {
  size_t pos = path.rfind(".");
  if ( path.substr(pos) == ".js" ) return "application/x-javascript";
  if ( path.substr(pos) == ".css" ) return "text/css";
  return "text/html; charset=UTF-8";
}
void process_request(WebServer::HttpReqResq * phttp) {
  struct evhttp_request * req =  phttp->req;
  struct evbuffer * buf =  phttp->buf;
  std::string path(evhttp_request_uri(req));
  if ( path.substr(0,5) == "/bin/" ) {
    std::string file =  path;
    size_t pos = file.find("?");
    if ( pos != file.npos) 
      file = file.substr(0,pos);
    pos = path.find("?");
    std::string query = "";
    if ( pos != path.npos) 
      query = path.substr(pos+1);
    std::string html;
    //获得post数据
    size_t post_size = EVBUFFER_LENGTH(req->input_buffer);
    std::string out(EVBUFFER_DATA(req->input_buffer),EVBUFFER_DATA(req->input_buffer) + post_size);
    const char * cookie_str = evhttp_find_header(evhttp_request_get_input_headers(req), "Cookie");
    std::string in_cookie = "";
    if (cookie_str) in_cookie = std::string(cookie_str);
    std::string cmd = "/usr/bin/python " + std::string() + web_dir_prefix + file + ".py " +
                                       "'" + query + "' " +
                                       "'" + in_cookie + "' " +
                                       "'" + out + "'";
    std::cerr << cmd << std::endl;
    RunCmdAndGetResult(cmd,&html);
    //获得cookie 
    auto poss = html.find(endheader);
    if (poss != html.npos) {
      std::string cookiestr = html.substr(0, poss);
      std::cerr << cookiestr << std::endl;
      //hash:5241bce5bbf0c5e7460bba7be0740dbf:/::0:false:false
      //username:peitaonnbbaa:/::0:false:false
      //设置cookie
      std::string line;
      std::stringstream sin(cookiestr);
      while(std::getline(sin,line)) {
        std::string value;
        auto f = line.find(":");
        value += line.substr(0,f) + "=";
        auto t = line.substr(f+1).find(":");
        value += line.substr(f+1).substr(0,t) + ";path=/";
        std::cerr << value << std::endl;
        evhttp_add_header(evhttp_request_get_output_headers(req),"Set-Cookie", value.c_str());
      }
    }
    //evbuffer_add_printf(buf,"%s",html.substr(poss + strlen(endheader)).c_str());
    std::string realhtml = html.substr(poss + strlen(endheader));
    evbuffer_add(buf,&realhtml[0],realhtml.size());
    evhttp_add_header(req->output_headers, "Content-Type", "text/html; charset=UTF-8");
    //std::ofstream aa("a");
    //aa<<html.substr(poss + strlen(endheader)).c_str()<<std::endl;
    phttp->done();
    return;
  } else {
    std::string file = web_dir_prefix + path;
    size_t pos = file.find("?");
    if ( pos != file.npos) 
      file = file.substr(0,pos);
    int fd = open(file.c_str(),O_RDONLY);
    if ( fd == -1 ) {
      phttp->done();
      return;
    }
    else {
      size_t file_size = get_file_size(file.c_str());
      void * file_buf = malloc(file_size);
      read(fd,file_buf,file_size);
      evbuffer_add(buf,file_buf,file_size);
      evhttp_add_header(req->output_headers, "Content-Type", get_file_content_type(file).c_str());
      if (file_buf) free(file_buf);
      close(fd);
      phttp->done();
    }
  }
}

int main(int argc, const char *argv[])
{
  WebServer server("0.0.0.0",10229,5,process_request);
  server.Init();
  server.Loop();
  std::cerr << "What is problem?" << std::endl;
  return 0;
}
