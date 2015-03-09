#include "baseindex.h"

bool BaseIndex::BuildIndexFromRawFile(const char * filename) {
  std::ifstream in(filename);
  if (!in) std::cerr << "Read Index File fail!" << std::endl;
  std::string line;
  while ( std::getline(in, line) ) {
    std::string fields;
    if ( !SplitString(line, &fields)) continue;
    if ( fields.size() != 2u ) continue;
      //
    }
  }
}
