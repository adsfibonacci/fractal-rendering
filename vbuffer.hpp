#ifndef _VBUFFER_
#define _VBUFFER_

#include "syshead.hpp"

class vbuffer {
private:
  unsigned int m_render_id;
public:
  vbuffer(const void* data, unsigned int size); //size refers the total byte size of the structure
  ~vbuffer();

  void bind() const;
  void unbind() const;
};

#endif //_VBUFFER_
