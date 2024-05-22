#ifndef _VERTEXARRAYS_
#define _VERTEXARRAYS_

#include "vbuffer.hpp"

enum class BITTYPE {
  UDEF=0,
  FLOAT=GL_FLOAT,
  UINT=GL_UNSIGNED_INT,
  UCHAR=GL_UNSIGNED_BYTE
};

struct vbufferelement {
  BITTYPE type = BITTYPE::UDEF;
  unsigned int count;
  unsigned char norm = GL_FALSE;

  unsigned int get_type() const;
  unsigned int get_size() const;
};

class vbufferlayout {
private:
  std::vector<vbufferelement> m_elements;
  unsigned int m_stride;

public:
  vbufferlayout();
  ~vbufferlayout();

  void push(vbufferelement data);
  unsigned int get_stride() const;
  unsigned int get_count() const;
  const vbufferelement& operator[](unsigned int index) const;
};

class varray {
private:
  unsigned int m_renderid;

public:
  varray();
  ~varray();

  void bind() const;
  void unbind() const;
  
  void addbuffer(const vbuffer& vb, const vbufferlayout& layout);

  varray* operator*();
  const varray* operator*() const;
  bool operator==(varray& other);
  bool operator==(const varray& other) const;
  
};

#endif //_VERTEXARRAYS_
