#include "camera.hpp"

camera::camera() : m_pos(glm::vec3(0.0f, 0.0f, 3.0f)), m_up(glm::vec3(0.0f, 1.0f, 0.0f)), m_front(glm::vec3(0.0f, 0.0f, -1.0f)) {
  m_proj = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1000.0f, 1000.0f);
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}
camera::~camera() {}

void camera::xdir_p(float x) {
  m_pos[0] += -x;
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);  
}
void camera::xdir_n(float x) {
  xdir_p(-x);
}
void camera::ydir_p(float y) {
  m_pos[1] += -y;
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}
void camera::ydir_n(float y) {
  ydir_p(-y);
}
void camera::zdir_p(float z) {
  m_pos[2] += -z;
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}
void camera::zdir_n(float z) {
  zdir_p(-z);
}

void camera::pitch_p(float p) {
  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), p, glm::vec3(1.0f, 0.0f, 0.0f));
  m_pos = glm::vec3(rot * glm::vec4(m_pos, 1.0f));
  m_up = glm::vec3(rot * glm::vec4(m_up, 1.0f));
  m_front = glm::vec3(rot * glm::vec4(m_front, 1.0f));
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}
void camera::pitch_n(float p) {
  pitch_p(-p);
}
void camera::yaw_p(float y) {
  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), y, glm::vec3(0.0f, 1.0f, 0.0f));
  m_pos = glm::vec3(rot * glm::vec4(m_pos, 1.0f));
  m_up = glm::vec3(rot * glm::vec4(m_up, 1.0f));
  m_front = glm::vec3(rot * glm::vec4(m_front, 1.0f));
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}
void camera::yaw_n(float y) {
  yaw_p(-y);
}
void camera::roll_p(float r) {
  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), r, glm::vec3(0.0f, 0.0f, 1.0f));
  m_pos = glm::vec3(rot * glm::vec4(m_pos, 1.0f));
  m_up = glm::vec3(rot * glm::vec4(m_up, 1.0f));
  m_front = glm::vec3(rot * glm::vec4(m_front, 1.0f));
  m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}
void camera::roll_n(float r) {
  roll_p(-r);
}

void camera::keyinputs(GLFWwindow *window, int key, int scancode, int action, int mods) {
  (void)scancode;

  camera* cam = static_cast<camera*>(glfwGetWindowUserPointer(window));
  const float speed = 1.0f;

  if(mods == GLFW_MOD_CONTROL && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
	switch(key) {
	case GLFW_KEY_W:
	  cam->pitch_p(speed/100);
	  break;
	case GLFW_KEY_A:
	  cam->roll_n(speed/100);
	  break;
	case GLFW_KEY_S:
	  cam->pitch_n(speed/100);
	  break;
	case GLFW_KEY_D:
	  cam->roll_p(speed/100);
	  break;
	default:
	  break;
	}
  }
  else if(action == GLFW_PRESS || action == GLFW_REPEAT) {
	switch(key) {
	case GLFW_KEY_W:
	  cam->ydir_p(speed);
	  break;
	case GLFW_KEY_A:
	  cam->xdir_n(speed);
	  break;
	case GLFW_KEY_S:
	  cam->ydir_n(speed);
	  break;
	case GLFW_KEY_D:
	  cam->xdir_p(speed);
	  break;
	default:
	  break;
	}
  }

}
void camera::scrollinputs(GLFWwindow *window, double xoffset, double yoffset) {
  (void)xoffset;
  unsigned int ctrl_key = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
  bool ctrl = (ctrl_key == GLFW_PRESS || ctrl_key == GLFW_REPEAT);
  const float speed = 1.0f;

  camera* cam = static_cast<camera*>(glfwGetWindowUserPointer(window));
  
  if(!ctrl) {
	if(yoffset > 0) cam->zdir_p(speed);
	else cam->zdir_n(speed);
  }
  else {
	if(yoffset > 0) cam->yaw_p(speed);
	else cam->yaw_n(speed);
  }
}

const glm::mat4 camera::view() const {
  return m_proj * m_view;
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
