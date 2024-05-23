#include "render.hpp"

render::render() {}
render::~render() {}

void render::add_mesh(varray* va, std::unordered_map<const ibuffer*, const shader*>& is) {
  if(m_varr.find(va) == m_varr.end()) {
	m_varr[va] = is;
  }
  else {
	m_varr[va].insert(is.begin(), is.end());
  }
}
void render::add_mesh(const varray* va, const std::unordered_map<const ibuffer*, const shader*>& is) {
  if(m_varr.find(va) == m_varr.end()) {
	m_varr[va] = is;
  }
  else {
	m_varr[va].insert(is.begin(), is.end());
  }
}
void render::unload() const {
  for(auto& [va, ub] : m_varr) {
	va->unbind();
	for(auto& [ib, shad] : ub) {
	  ib->unbind();
	  shad->unbind();
	}
  }
}
void render::draw() const {
  for(auto& [va, ub] : m_varr) {
	va->bind();
	for(auto& [ib, shad] : ub) {
	  ib->bind();
	  shad->bind();
	  GLCall(glDrawElements(GL_TRIANGLES, ib->get_count(), GL_UNSIGNED_INT, nullptr));
	}
  }
}
void render::clear() const {
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
