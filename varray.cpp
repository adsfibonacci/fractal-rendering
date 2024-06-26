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
  if(m_vertex_data.find(&vb) != m_vertex_data.end()) {
	std::cerr << "[WARNING]: VERTEXBUFFER ALREADY DEFINED" << std::endl;
	return;
  }
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
void varray::addbuffer(const std::unordered_map<const vbuffer*, const vbufferlayout*>& umap) {
  for(const auto& [vb, layout] : umap) {
	addbuffer(*vb, *layout);
  }
}

std::unordered_map<const vbuffer*, const vbufferlayout*> varray::getbuffer() const {
  return m_vertex_data;
}

varray& varray::operator=(varray& other) {
  if(this != &other) {
	GLCall(glGenVertexArrays(1, &m_renderid));
	addbuffer(other.getbuffer());
  }
  return *this;
}
varray& varray::operator=(const varray& other) {
  if(this != &other) {
	GLCall(glGenVertexArrays(1, &m_renderid));
	addbuffer(other.getbuffer());
  }
  return *this;
}
