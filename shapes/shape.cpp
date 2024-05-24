#include "shape.hpp"

shape::shape(unsigned int s, const shader* shad) : m_shad(shad) {
  m_data.reserve(s);
}
shape::~shape() {}

const ibuffer* shape::get_index_buffer() const {
  return &m_ib;
}
const vbuffer* shape::get_vertex_buffer() const {
  return &m_vb;
}
const varray* shape::get_vertex_array() const {
  return &m_va;
}
const std::unordered_map<const ibuffer*, const shader*>& shape::get_mapping() const {
  return m_umap;
}
