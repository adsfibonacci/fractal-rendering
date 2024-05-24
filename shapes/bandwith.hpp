#ifndef _BANDREGION_
#define _BANDREGION_

#include "shape.hpp"

class band : public shape {
private:
  unsigned int m_index;
  
public:
  band(std::vector<float> s1, std::vector<float> s2, const shader* shad);
  ~band();

  void addvertices() override;
  void addindexing() override;
  void addshading() override;
};

#endif //_BANDREGION_
