#ifndef _IBUFFER_
#define _IBUFFER_

#include "syshead.hpp"

class ibuffer {
private:
  unsigned int m_render_id;
  unsigned int m_count;
public:
  ibuffer(const unsigned int* data, unsigned int count); //count is the number of elements in structure
  ~ibuffer();

  void bind() const;
  void unbind() const;
  
  unsigned int get_count() const;  
};

#endif //_IBUFFER_
