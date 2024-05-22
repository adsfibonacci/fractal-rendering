#include "varray.hpp"

unsigned int vbufferelement::get_type() const {
  return (unsigned int)type;
}

unsigned int vbufferelement::get_size() const {
  unsigned int ret = count;
  switch (type) {
  case BITTYPE::FLOAT:
	ret *= sizeof(GLfloat);
	break;
  case BITTYPE::UINT:
	ret *= sizeof(GLuint);
	break;
  case BITTYPE::UCHAR:
	ret *= sizeof(GLbyte);
	break;
  default:
	ret *= 0;
  }
  return ret;
}

vbufferlayout::vbufferlayout() : m_stride(0) {}
vbufferlayout::~vbufferlayout() {}

void vbufferlayout::push(vbufferelement vbe) {
  assert(vbe.type != BITTYPE::UDEF);
  m_elements.push_back(vbe);
  m_stride += vbe.get_size();
}

unsigned int vbufferlayout::get_stride() const {
  return m_stride;
}

unsigned int vbufferlayout::get_count() const {
  return m_elements.size();
}

const vbufferelement& vbufferlayout::operator[](unsigned int index) const {
  return m_elements[index];
}




varray::varray() {
  GLCall(glGenVertexArrays(1, &m_renderid));
}
varray::~varray() {
  GLCall(glDeleteVertexArrays(1, &m_renderid));
}

void varray::bind() const {
  GLCall(glBindVertexArray(m_renderid));
}

void varray::unbind() const {
  GLCall(glBindVertexArray(0));
}

void varray::addbuffer(const vbuffer& vb, const vbufferlayout& layout) {
  bind();
  vb.bind();

  unsigned int offset = 0;
  
  for(unsigned int i = 0; i < layout.get_count(); ++i) {
	const vbufferelement tmp = layout[i];
	GLCall(glEnableVertexAttribArray(i));
	GLCall(glVertexAttribPointer(i, tmp.count, tmp.get_type(), tmp.norm, layout.get_stride(), (const void*)((long) offset)));

	offset += tmp.count * tmp.get_size();
  }
}

varray* varray::operator*() {
  return this;
}

const varray* varray::operator*() const {
  return this;
}

bool varray::operator==(varray& other) {
  return this == &other;
}

bool varray::operator==(const varray& other) const {
  return this == &other;
}
