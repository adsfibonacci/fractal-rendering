#ifndef _CAMERA_
#define _CAMERA_

#include "syshead.hpp"

class camera {
private:
  glm::mat4 m_view;
  glm::mat4 m_proj;

  glm::vec3 m_pos;
  glm::vec3 m_up;
  glm::vec3 m_front;

public:
  camera();
  ~camera();
  
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

  void inputs(GLFWwindow *window);
  static void keyinputs(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void scrollinputs(GLFWwindow *window, double xoffset, double yoffset);

  const glm::mat4 view() const;
};

std::ostream& operator<<(std::ostream& os, const camera& cam);

#endif //_CAMERA_
