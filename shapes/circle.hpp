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
  float m_radius;

  float m_angle;

  std::tuple<float, float> m_offset;
  std::vector<float> m_circumference;
  std::vector<unsigned int> m_indexing;
  std::unordered_map<const ibuffer*, const shader*> m_umap;

  varray va;
  vbuffer vb;
  vbufferlayout layout;
  ibuffer ib;
  const shader* m_shad;

public:
  circle(std::pair<float, float> off, float r, unsigned int s, const shader* shad);
  ~circle();
  void addvertices();
  void addindexing();
  void addshading();

  const ibuffer* get_index_buffer() const;
  const vbuffer* get_vertex_buffer() const;
  const varray* get_vertex_array() const;
  const std::unordered_map<const ibuffer*, const shader*>& get_mapping() const;
};

#endif //_CIRCLE2D_
