#include "circle.hpp"

circle::circle(std::pair<float, float> off, unsigned int r, unsigned int s) : m_samples(s), m_radius(r), m_angle(2 * PI / m_samples), m_offset({off.first, off.second}) {
  
  m_circumference.reserve(s);

  addvertices();
  addindexing();
}
circle::~circle() {}

void circle::addvertices() {
  std::vector<float> vec;
  vec.reserve(m_samples);
  float curr_angle = 0;
  float curr_coord = 0;
  for(unsigned int i = 0; i < m_samples; ++i) {
	curr_coord = (float)m_radius * cos(curr_angle);
	m_circumference.push_back(curr_coord);
	curr_coord = (float)m_radius * sin(curr_angle);
	m_circumference.push_back(curr_coord);
	curr_angle += m_angle;
	m_circumference.push_back(0.0f);
  }
}
void circle::addindexing() {
  unsigned int index1 = 0;
  unsigned int index2 = 1;
  unsigned int index3 = 2;
  for(unsigned int i = 0; i < m_samples - 2; ++i) {
	index2 += i;
	index3 += i;
	m_indexing.push_back(index1);
	m_indexing.push_back(index2);
	m_indexing.push_back(index3);	
  }
}

std::pair<vbuffer, vbufferlayout> circle::get_vertex_data() {
  
  vbuffer vb(&m_circumference, m_circumference.size() * sizeof(float));
  vbufferlayout layout;
  layout.push({BITTYPE::FLOAT, 3});
  return {vb, layout};
}
