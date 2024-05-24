#ifndef _SHAPE_
#define _SHAPE_

#include "../syshead.hpp"
#include "../varray.hpp"
#include "../vbuffer.hpp"
#include "../ibuffer.hpp"
#include "../shader.hpp"

const float PI = 2*acos(0.0);

class shape {
private:
protected:
  std::vector<float> m_data;
  std::vector<unsigned int> m_indexing;
  std::unordered_map<const ibuffer*, const shader*> m_umap;

  varray m_va;
  vbuffer m_vb;
  vbufferlayout m_layout;
  ibuffer m_ib;
  const shader* m_shad;
  
public:
  shape(unsigned int s, const shader* shad);
  ~shape();

  virtual void addvertices() = 0;
  virtual void addindexing() = 0;
  virtual void addshading() = 0;

  const ibuffer* get_index_buffer() const;
  const vbuffer* get_vertex_buffer() const;
  const varray* get_vertex_array() const;
  const std::unordered_map<const ibuffer*, const shader*>& get_mapping() const;
};

#endif //_SHAPE_
