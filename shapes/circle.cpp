#include "circle.hpp"

circle::circle(std::pair<float, float> off, float r, unsigned int s, const shader* shad) : m_samples(s), m_radius(r), m_angle(2 * PI / m_samples), m_offset({off.first, off.second}), m_shad(shad) {
  
  m_circumference.reserve(s);

  addvertices();
  addindexing();

  vbuffer vbufftemp(&m_circumference[0], m_circumference.size() * sizeof(float));
  vb = vbufftemp;  
  layout.push({BITTYPE::FLOAT, 3});
  va.addbuffer(vb, layout);
  ibuffer ibufftemp(&m_indexing[0], m_indexing.size());  
  ib = ibufftemp;
  m_umap[&ib] = shad;
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
	m_indexing.push_back(index1);
	m_indexing.push_back(index2);
	m_indexing.push_back(index3);
	index2++;
	index3++;
  }
}
void circle::addshading() {
  m_umap[&ib] = m_shad;
}

const ibuffer* circle::get_index_buffer() const {
  return &ib;
}
const vbuffer* circle::get_vertex_buffer() const {
  return &vb;
}
const varray* circle::get_vertex_array() const {
  return &va;
}
const std::unordered_map<const ibuffer*, const shader*>& circle::get_mapping() const {
  return m_umap;
}
