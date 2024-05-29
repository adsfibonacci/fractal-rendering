#ifndef _SYSHEAD_
#define _SYSHEAD_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <cassert>
#include <typeinfo>
#include <climits>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct material {
  float col[3];
};
struct light {
  float col[3];
};
struct mvp {
  glm::mat4 proj;
  glm::mat4 view;
  glm::mat4 mode;
};

const unsigned int vertex_size = 3;
const unsigned int point_count = 4;
const unsigned int triangle_count = 2;

class null {
private:
  null() {
	(void)vertex_size;
	(void)point_count;
	(void)triangle_count;
  }
};

#endif //_SYSHEAD_

#ifndef _GLERRORS_
#define _GLERRORS_

#define GLCall(x) GLClearError(); \
  x;\
  assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

std::ostream& operator<<(std::ostream& os, glm::vec4& v);
std::ostream& operator<<(std::ostream& os, glm::mat4& m);

#endif //_GLERRORS_
