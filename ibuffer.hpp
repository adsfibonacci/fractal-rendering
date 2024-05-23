#ifndef _IBUFFER_
#define _IBUFFER_

#include "syshead.hpp"

class ibuffer {
private:
  unsigned int m_render_id;
  const unsigned int* m_data;
  unsigned int m_count;
  
public:
  ibuffer();
  ibuffer(const unsigned int* data, unsigned int count); //count is the number of elements in structure
  ~ibuffer();

  void bind() const;
  void unbind() const;
  
  unsigned int get_count() const;
  const unsigned int* get_data() const;

  ibuffer& operator=(ibuffer& other);
  ibuffer& operator=(const ibuffer& other);
};

#endif //_IBUFFER_
