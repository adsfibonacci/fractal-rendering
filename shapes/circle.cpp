#include "circle.hpp"

circle::circle(std::pair<float, float> off, float r, unsigned int s, const shader* shad) :  shape(s, shad), m_samples(s), m_radius(r), m_angle(2 * PI / m_samples), m_offset({off.first, off.second}) {
  addvertices();
  addindexing();
  addshading();
}
circle::~circle() {}

void circle::addvertices() {
  float curr_angle = 0;
  float curr_coord = 0;
  for(unsigned int i = 0; i < m_samples; ++i) {
	curr_coord = (float)m_radius * cos(curr_angle);
	m_data.push_back(curr_coord);
	curr_coord = (float)m_radius * sin(curr_angle);
	m_data.push_back(curr_coord);
	curr_angle += m_angle;
	m_data.push_back(0.0f);
  }
  m_vb = vbuffer(&m_data[0], m_data.size() * sizeof(float));
  m_layout.push({BITTYPE::FLOAT, 3});
  m_va.addbuffer(m_vb, m_layout);
}
void circle::addindexing() {
  unsigned int index1 = 0;
  unsigned int index2 = 1;
  unsigned int index3 = 2;
  for(unsigned int i = 0; i < m_samples - 2; ++i, ++index2, ++index3) {
	m_indexing.push_back(index1);
	m_indexing.push_back(index2);
	m_indexing.push_back(index3);
  }
  m_ib = ibuffer(&m_indexing[0], m_indexing.size());
}
void circle::addshading() {
  m_umap[&m_ib] = m_shad;
}
