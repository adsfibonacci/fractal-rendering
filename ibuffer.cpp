#include "ibuffer.hpp"

ibuffer::ibuffer(const unsigned int* data, unsigned int count) : m_count(count) {
  GLCall(glGenBuffers(1, &m_render_id));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
}
ibuffer::~ibuffer() {
  GLCall(glDeleteBuffers(1, &m_render_id));
}

void ibuffer::bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id));
}
void ibuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int ibuffer::get_count() const {
  return m_count;
}
