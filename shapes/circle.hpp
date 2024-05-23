#include "../syshead.hpp"
#include "../varray.hpp"
#include "../vbuffer.hpp"
#include "../ibuffer.hpp"
#include "../shader.hpp"

#include <cmath>

const float PI = 2*acos(0.0);

#ifndef _CIRCLE2D_
#define _CIRCLE2D_

class circle {
private:
  unsigned int m_samples;
  unsigned int m_radius;

  float m_angle;

  std::tuple<float, float> m_offset;
  std::vector<float> m_circumference;
  std::vector<unsigned int> m_indexing;

public:
  circle(std::pair<float, float> off, unsigned int r, unsigned int s);
  ~circle();
  void addvertices();
  void addindexing();

  std::pair<vbuffer, vbufferlayout> get_vertex_data();
};

#endif //_CIRCLE2D_
