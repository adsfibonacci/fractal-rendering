#include "ibuffer.hpp"

ibuffer::ibuffer() : m_data(nullptr), m_count(0) {
  GLCall(glGenBuffers(1, &m_render_id));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
ibuffer::ibuffer(const unsigned int* data, unsigned int count) : m_data(data), m_count(count) {
  GLCall(glGenBuffers(1, &m_render_id));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), m_data, GL_DYNAMIC_DRAW));
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
const unsigned int* ibuffer::get_data() const {
  return m_data;
}

ibuffer& ibuffer::operator=(ibuffer& other) {
  if(this != &other) {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glDeleteBuffers(1, &m_render_id));
	m_data = other.get_data();
	m_count = other.get_count();
	GLCall(glGenBuffers(1, &m_render_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), m_data, GL_DYNAMIC_DRAW));
  }
  return *this;
}
ibuffer& ibuffer::operator=(const ibuffer& other) {
  if(this != &other) {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glDeleteBuffers(1, &m_render_id));
	m_data = other.get_data();
	m_count = other.get_count();
	GLCall(glGenBuffers(1, &m_render_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), m_data, GL_DYNAMIC_DRAW));
  }
  return *this;
}
