#ifndef UTIL_5WM3X5UM

#define UTIL_5WM3X5UM
#include <vector>
#include <string>
#include <map>
bool SplitStringRemoveEmpty(const std::string & src, const std::string & sp, std::vector<std::string> * result);
bool SplitString(const std::string & src, const std::string & sp, std::vector<std::string> * result);
bool ParseHttpParms(const std::string & str,std::map<std::string,std::string> * result);
#endif /* end of include guard: UTIL_5WM3X5UM */
