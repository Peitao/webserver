#ifndef BASEINDEX_H

#define BASEINDEX_H

class BaseIndex {
public:
  bool BuildIndexFromRawFile(const char * filename);
  typedef std::unordered_map<std::string, std::vector<size_t> MInvertIndexType;
  typedef std::unordered_map<std::string, std::vector<std::string> SInvertIndexType;
private:
  //二级索引
  static const int MGRAM = 2;
  static const int SGRAM = 1;
  MInvertIndexType mindex;
  SInvertIndexType sindex;
  std::vector<std::string> docs;
};

#endif /* end of include guard: BASEINDEX_H */
