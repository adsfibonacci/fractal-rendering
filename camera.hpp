#ifndef _CAMERA_
#define _CAMERA_

#include "syshead.hpp"

class camera {
private:
  glm::mat4 m_view;
  float m_global_x;
  float m_global_y;
  float m_global_z;
public:
  camera();
  ~camera();

  void set_global(glm::vec3 v) {
	m_global_x = v[0];
	m_global_y = v[1];
	m_global_y = v[2];
  }

  void xdir_p(float x);
  void xdir_n(float x);
  void ydir_p(float y);
  void ydir_n(float y);
  void zdir_p(float z);
  void zdir_n(float z);

  void pitch_p(float p);
  void pitch_n(float p);
  void yaw_p(float y);
  void yaw_n(float y);
  void roll_p(float r);
  void roll_n(float r);

  const glm::mat4& view() const;
};

std::ostream& operator<<(std::ostream& os, const camera& cam);

#endif //_CAMERA_
