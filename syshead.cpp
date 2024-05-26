#include "syshead.hpp"

void GLClearError() {
  while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
  while(GLenum error = glGetError()) {
	std::cout << "[OpenGL]: " << std::hex << error << std::endl;
	std::cout << file << ":\t" << function << ":\t" << line << std::endl;
	return false;
  }  
  return true;
}

std::ostream& operator<<(std::ostream& os, glm::vec4& v) {
  os << v.x << "\t" << v.y << "\t" << v.z << "\t" << v.w;
  return os;
}
std::ostream& operator<<(std::ostream& os, glm::mat4& m) {
  for(unsigned int i = 0; i < 4; ++i) {
	for(unsigned int j = 0; j < 4; ++j) {
	  os << m[i][j] << "\t";
	}
	os << std::endl;
  }
  return os;
}
