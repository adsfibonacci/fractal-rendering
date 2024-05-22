#include "vbuffer.hpp"

vbuffer::vbuffer(const void* data, unsigned int size) {
  GLCall(glGenBuffers(1, &m_render_id));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_render_id));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}
vbuffer::~vbuffer() {
  GLCall(glDeleteBuffers(1, &m_render_id));
}

void vbuffer::bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_render_id));
}
void vbuffer::unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
