#ifndef _CIRCLE2D_
#define _CIRCLE2D_

#include "shape.hpp"

class circle : public shape {
private:
  unsigned int m_samples;
  float m_radius;
  float m_angle;
  std::tuple<float, float> m_offset;

public:
  circle(std::pair<float, float> off, float r, unsigned int s, const shader* shad);
  ~circle();
  void addvertices() override;
  void addindexing() override;
  void addshading() override;
};

#endif //_CIRCLE2D_
