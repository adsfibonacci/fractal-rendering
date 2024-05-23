#ifndef _VBUFFER_
#define _VBUFFER_

#include "syshead.hpp"

class vbuffer {
private:
  unsigned int m_render_id;
  const void* m_data;
  unsigned int m_size;
  
public:
  vbuffer();
  vbuffer(const void* data, unsigned int size); //size refers the total byte size of the structure
  ~vbuffer();

  void bind() const;
  void unbind() const;

  const void* get_data() const;
  unsigned int get_size() const;

  vbuffer& operator=(vbuffer& other);
  vbuffer& operator=(const vbuffer& other);
};

#endif //_VBUFFER_
