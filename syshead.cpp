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
