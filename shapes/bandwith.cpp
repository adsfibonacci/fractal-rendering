#include "bandwith.hpp"

band::band(std::vector<float> s1, std::vector<float> s2, const shader* shad) : shape((unsigned int)(s1.size() == s2.size() * s1.size() * 2), shad), m_index(s1.size()){
  
  m_data.insert(m_data.end(), s1.begin(), s1.end());
  m_data.insert(m_data.end(), s2.begin(), s2.end());

  addvertices();
  addindexing();
  addshading();
}
band::~band() {}

void band::addvertices() {
  m_vb = vbuffer(&m_data[0], m_data.size() * sizeof(float));
  m_layout.push({BITTYPE::FLOAT, 3});
  m_va.addbuffer(m_vb, m_layout);
}
void band::addindexing() {
  for(unsigned int i = 0, j = m_index/3; i < m_index/3 - 1; ++i, ++j) {
	m_indexing.push_back(i);
	m_indexing.push_back(i+1);
	m_indexing.push_back(j);
	m_indexing.push_back(j);
	m_indexing.push_back(j+1);
	m_indexing.push_back(i+1);
  }
  m_ib = ibuffer(&m_indexing[0], m_indexing.size());
}
void band::addshading() {
  m_umap[&m_ib] = m_shad;
}
