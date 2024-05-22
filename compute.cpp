#include "syshead.hpp"
#include "render.hpp"
#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "varray.hpp"
#include "shader.hpp"

#include <map>

int main() {
  if (!glfwInit()){
	std::cout << "GLFW Failed" << std::endl;
	return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "Fractals", NULL, NULL);
  
  if (!window) {
	std::cout << "Window Failed" << std::endl;
	glfwTerminate();
	return -1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSwapInterval(10);

  if(glewInit() != GLEW_OK) {
	std::cout << "GLEW Error" << std::endl;
	return -1;
  }

  //std::cout << sizeof(GLbyte) << std::endl;
  
  float positions[(2 * point_count - 1) * vertex_size] = {
	-1.0f, -1.0f, 0.0f,
	+0.0f, -1.0f, 0.0f,
	+0.0f, +0.0f, 0.0f,
	-1.0f, +0.0f, 0.0f,
	+1.0f, +0.0f, 0.0f,
	+1.0f, +1.0f, 0.0f,
	+0.0f, +1.0f, 0.0f
  };
  unsigned int indices[3 * triangle_count] = {
	0, 1, 2,
	2, 3, 0
  };
  unsigned int order[3 * triangle_count] = {
	2, 4, 5,
	5, 6, 2
  };

  varray va;
  vbuffer vb(positions, (2 * point_count - 1) * vertex_size * sizeof(float));

  vbufferlayout layout;
  layout.push({BITTYPE::FLOAT, vertex_size});
  va.addbuffer(vb, layout);
  
  ibuffer ib(indices, 6);
  ibuffer ibb(order, 6);
  
  float i = +0.05f;
  
  float currTime = static_cast<float>(glfwGetTime());;

  float ucolor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  float& r = ucolor[0];
  shader shad("shaders/vertex.shader", "shaders/fragment.shader");
  shad.bind();
  shad.uniform4f("u_Color", ucolor);
  shad.uniform1f("u_Time", currTime);

  std::unordered_map<const ibuffer*, const shader*> umap;
  umap[&ib] = &shad;
  umap[&ibb] = &shad;

  render rend;
  rend.add_mesh(&va, umap);
  rend.unload();
  
  while (!glfwWindowShouldClose(window)) {
	rend.clear();

	currTime = static_cast<float>(glfwGetTime());
	rend.draw();
	
	shad.bind();
	shad.uniform4f("u_Color", ucolor);
	shad.uniform1f("u_Time", currTime);	

	if (r >= 1.0f) i = -0.05f;
	if (r <= 0.0f) i = +0.05f;
	
	r += i;

	glfwSwapBuffers(window);
	glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}
