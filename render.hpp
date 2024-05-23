#ifndef _RENDER_
#define _RENDER_

#include "syshead.hpp"
#include "varray.hpp"
#include "ibuffer.hpp"
#include "shader.hpp"

class render {
private:
  std::unordered_map<const varray*, std::unordered_map<const ibuffer*, const shader*>> m_varr;
  
public:
  render();
  ~render();
  
  void add_mesh(varray* va, std::unordered_map<const ibuffer*, const shader*>& ibs);
  void add_mesh(const varray* va, const std::unordered_map<const ibuffer*, const shader*>& ibs);
  void unload() const;
  void draw() const;
  void clear() const;
};

#endif //_RENDER_
