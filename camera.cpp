#include "camera.hpp"

camera::camera() : m_view(glm::mat4(1.0f)), m_global_x(0), m_global_y(0), m_global_z(0) {}
camera::~camera() {}

void camera::xdir_p(float x) {
  m_view = glm::translate(m_view, glm::vec3(-x, 0.0f, 0.0f));
  m_global_x -= x;
}
void camera::xdir_n(float x) {
  m_view = glm::translate(m_view, glm::vec3(x, 0.0f, 0.0f));
  m_global_x += x;
}
void camera::ydir_p(float y) {
  m_view = glm::translate(m_view, glm::vec3(0.0f, -y, 0.0f));
  m_global_y -= y;
}
void camera::ydir_n(float y) {
  m_view = glm::translate(m_view, glm::vec3(0.0f, y, 0.0f));
  m_global_y += y;
}
void camera::zdir_p(float z) {
  m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -z));
  m_global_z -= z;
}
void camera::zdir_n(float z) {
  m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, z));
  m_global_z += z;
}

void camera::pitch_p(float p) {
  m_view = glm::translate(m_view, glm::vec3(m_global_x, m_global_y, m_global_z));
  m_view = glm::rotate(m_view, -p, glm::vec3(1.0f, 0.0f, 0.0f));
  m_view = glm::translate(m_view, -glm::vec3(m_global_x, m_global_y, m_global_z));
}
void camera::pitch_n(float p) {
  pitch_p(-p);
}
void camera::yaw_p(float y) {
  m_view = glm::translate(m_view, glm::vec3(m_global_x, m_global_y, m_global_z));
  m_view = glm::rotate(m_view, -y, glm::vec3(0.0f, 1.0f, 0.0f));
  m_view = glm::translate(m_view, -glm::vec3(m_global_x, m_global_y, m_global_z));
}
void camera::yaw_n(float y) {
  yaw_p(-y);
}
void camera::roll_p(float r) {
  m_view = glm::translate(m_view, glm::vec3(m_global_x, m_global_y, m_global_z));
  m_view = glm::rotate(m_view, -r, glm::vec3(0.0f, 0.0f, 1.0f));
  m_view = glm::translate(m_view, -glm::vec3(m_global_x, m_global_y, m_global_z));
}
void camera::roll_n(float r) {
  roll_p(-r);
}

const glm::mat4& camera::view() const {
  return m_view;
}

std::ostream& operator<<(std::ostream& os, const camera& cam) {
  for(unsigned int i = 0; i < 4; ++i) {
	for(unsigned int j = 0; j < 4; ++j) {
	  os << cam.view()[i][j] << "\t";
	}
	os << "\n";
  }
  return os;
}
