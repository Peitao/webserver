#include "util.h"
#include <iostream>
#include <map>

bool SplitStringDo(const std::string & src, const std::string & sp, std::vector<std::string> * result, bool remove) {
  if ( sp.size() == 0 ) return false;
  (*result).clear();
  size_t pos_from = 0;
  size_t pos_to = 0;
  do {
    pos_to = src.find(sp, pos_from);
    if ( pos_to == std::string::npos ) break;
    std::string substr = src.substr(pos_from, pos_to - pos_from);
    if (substr.size() || remove == false) (*result).push_back(substr);
    pos_from = pos_to + sp.size();
  } while (true);
  if ( pos_from != src.size() ) (*result).push_back(src.substr(pos_from));
  if ( pos_from == src.size() && remove == false) (*result).push_back(std::string());
  return true;
}

bool SplitString(const std::string & src, const std::string & sp, std::vector<std::string> * result) {
  return SplitStringDo(src, sp, result, false);
}
bool SplitStringRemoveEmpty(const std::string & src, const std::string & sp, std::vector<std::string> * result) {
  return SplitStringDo(src, sp, result, true);
}
// 输入:q=123&b=456&debug&&
// 输出:{"q":"123","b":"456","debug":""}
bool ParseHttpParms(const std::string & str,std::map<std::string,std::string> * result) {
  (*result).clear();
  if (!str.size()) return true;
  std::vector<std::string> params;
  SplitStringRemoveEmpty(str, "&", &params);
  for (auto it = params.begin(); it != params.end(); it++) {
    std::vector<std::string> fields;
    SplitStringRemoveEmpty(*it, "=", &fields);
    if (fields.size() == 2u) {
      (*result)[fields[0]] = fields[1];
    } else {
      (*result)[fields[0]] = std::string("");
    }
  }
  return true;
}
/*
void print(std::vector<std::string> result) {
  for (std::vector<std::string>::iterator it = result.begin(); it != result.end(); it++) {
    std::cout << "\"" << *it << "\" ";
  }
  std::cout << std::endl;
}
void print(std::map<std::string,std::string> result) {
  for (auto it = result.begin(); it != result.end(); it++) {
    std::cout << it->first << " " << it->second << std::endl;
  }
}


int main(int argc, const char *argv[])
{
  std::vector<std::string> result;
  SplitString("aaa12bbb12ccc","12",&result);
  print(result); 
  SplitString("aaa12bbb12","12",&result);
  print(result); 
  SplitString("aaa12","12",&result);
  print(result); 
  SplitString("1212","12",&result);
  print(result); 
  SplitString("aaa1212bbb12ccc","12",&result);
  print(result); 
  SplitString("12","12",&result);
  print(result); 
  SplitString("1","12",&result);
  print(result); 

  SplitStringRemoveEmpty("aaa12bbb12ccc","12",&result);
  print(result); 
  SplitStringRemoveEmpty("aaa12bbb12","12",&result);
  print(result); 
  SplitStringRemoveEmpty("aaa12","12",&result);
  print(result); 
  SplitStringRemoveEmpty("1212","12",&result);
  print(result); 
  SplitStringRemoveEmpty("aaa1212bbb12ccc","12",&result);
  print(result); 
  SplitStringRemoveEmpty("12","12",&result);
  print(result); 
  SplitStringRemoveEmpty("1","12",&result);
  print(result); 
  std::map<std::string,std::string> mm;
  ParseHttpParms("q=123&b=456&debug&&", &mm);
  print(mm);
  return 0;
}*/
