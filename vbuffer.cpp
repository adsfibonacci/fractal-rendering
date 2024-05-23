#include "vbuffer.hpp"
vbuffer::vbuffer() : m_data(nullptr), m_size(0) {
  GLCall(glGenBuffers(1, &m_render_id));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_render_id));
}
vbuffer::vbuffer(const void* data, unsigned int size) : m_data(data), m_size(size) {  
  GLCall(glGenBuffers(1, &m_render_id));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_render_id));
  GLCall(glBufferData(GL_ARRAY_BUFFER, m_size, m_data, GL_DYNAMIC_DRAW));
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

const void* vbuffer::get_data() const {
  return m_data;
}

unsigned int vbuffer::get_size() const {
  return m_size;
}

vbuffer& vbuffer::operator=(vbuffer& other) {
  if(this != &other) {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glDeleteBuffers(1, &m_render_id));
	m_data = other.get_data();
	m_size = other.get_size();
	GLCall(glGenBuffers(1, &m_render_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_render_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_size, m_data, GL_DYNAMIC_DRAW));
  }
  return *this;
}
vbuffer& vbuffer::operator=(const vbuffer& other) {
  if(this != &other) {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glDeleteBuffers(1, &m_render_id));
	m_data = other.get_data();
	m_size = other.get_size();
	GLCall(glGenBuffers(1, &m_render_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_render_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_size, m_data, GL_DYNAMIC_DRAW));
  }
  return *this;
}
