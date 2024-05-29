#include "syshead.hpp"
#include "render.hpp"
#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "varray.hpp"
#include "shader.hpp"
#include "shapes/circle.hpp"
#include "shapes/bandwith.hpp"

int main() {

  unsigned int w = 960;
  unsigned int h = 540;
  if (!glfwInit()){
	std::cout << "GLFW Failed" << std::endl;
	return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(w, h, "Fractals", NULL, NULL);
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
  float angle_inc = +0.001f;
  
  float curr_time = static_cast<float>(glfwGetTime());;

  float fragment_color[4] = {0.5f, 0.5f, 0.5f, 1.0f};  
  float& r = fragment_color[0];
  //float angle = 0.0f;
  //float angle_increment = .05f;
  float angle = 0.0f;
  glm::vec3 rot{0.5f, 1.0f, 0.0f};
  glm::mat4 trans(1.0f);
  trans = glm::ortho(0.0f, (float)w, 0.0f, (float)h, 0.0f, 1000.0f);
  trans = glm::rotate(trans, angle, rot);
  //trans = glm::scale(trans, glm::vec3(.90f, 1.60f, 1.0f));

  std::pair<const std::string, const std::string> paths = {
	"shaders/vertex.shader",
	"shaders/fragment.shader"
  };

  material bronze{{0.4f, 0.8f, 0.1f}};
  light orange{{0.8f, 0.7f, 0.6f}};
  
  shader shad(paths);
  shad.bind();
  //shad.uniform4vf("u_frag_color", fragment_color);
  shad.uniform1vf("u_Time", curr_time);
  shad.uniform4mf("u_Shift", trans);
  shad.uniform_material("u_bronze", bronze);
  shad.uniform_light_source("u_orange", orange);
  
  //std::unordered_map<const ibuffer*, const shader*> umap;
  //umap[&ib] = &shad;
  //umap[&ibb] = &shad;
  //
  //std::vector<float> line1 = {
  //	0.0f, 0.8f, 0.0f,
  //	0.25f, 0.7f, 0.0f,
  //	0.5f, 0.5f, 0.0f,
  //	0.8f, 0.0f, 0.0f,
  //	0.5f, -0.5f, 0.0f,
  //	0.25f, -0.7f, 0.0f,
  //	0.0f, -0.8f, 0.0f,
  //	-0.25f, -0.7f, 0.0f,
  //	-0.5f, -0.5f, 0.0f,
  //	-0.8f, -0.0f, 0.0f,
  //	-0.5f, 0.5f, 0.0f,
  //	-0.25f, 0.7f, 0.0f,
  //	0.0f, 0.8f, 0.0f
  //};
  //std::vector<float> line2 = {
  //	0.0f, 0.25f, 0.0f,
  //	0.15f, 0.20, 0.0f,
  //	0.20f, 0.15f, 0.0f,
  //	0.25f, 0.0f, 0.0f,
  //	0.20f, -0.15f, 0.0f,
  //	0.15f, -0.20f, 0.0f,
  //	0.0f, -0.25f, 0.0f,
  //	-0.15f, -0.20f, 0.0f,
  //	-0.20f, -0.15f, 0.0f,
  //	-0.25f, -0.0f, 0.0f,
  //	-0.20f, 0.15f, 0.0f,
  //	-0.15f, 0.20f, 0.0f,
  //	0.0f, 0.25f, 0.0f
  //};
  //circle c({0.0f, 0.0f}, 0.5f, 1000, &shad);
  //band b(line1, line2, &shad);

  float cube[8 * 3] = {
	100.0f, 100.0f, 0.0f,
	100.0f, 300.0f, 0.0f,
	300.0f, 300.0f, 0.0f,
	300.0f, 100.0f, 0.0f,
	100.0f, 100.0f, 100.0f,
	100.0f, 300.0f, 100.0f,
	300.0f, 300.0f, 100.0f,
	300.0f, 100.0f, 100.0f,
  };
  unsigned int cube_indices[6 * 2 * 3] {
	0, 1, 2,
	2, 3, 0,
	
	4, 5, 6,
	6, 7, 4,
	
	0, 1, 4,
	4, 5, 1,
	
	1, 2, 5,
	5, 6, 2,

	2, 3, 6,
	6, 7, 3,

	0, 3, 4,
	4, 7, 3
  };
  varray cube_array;
  vbuffer cube_vbuffer(cube, 8*3*sizeof(float));
  cube_array.addbuffer(cube_vbuffer, layout);
  ibuffer cube_ibuffer(cube_indices, 6*2*3);
  
  std::unordered_map<const ibuffer*, const shader*> cube_map;
  cube_map[&cube_ibuffer] =  &shad;

  render rend;
  rend.add_mesh(&cube_array, cube_map);
  //rend.add_mesh(b.get_vertex_array(), b.get_mapping());
  //rend.add_mesh(c.get_vertex_array(), c.get_mapping());
  //rend.add_mesh(&va, umap);
  
  rend.unload();
      
  while (!glfwWindowShouldClose(window)) {
	rend.clear();

	//curr_time = static_cast<float>(glfwGetTime());
	rend.draw();
	
	shad.bind();
	//shad.uniform4vf("u_frag_color", fragment_color);
	shad.uniform1vf("u_Time", curr_time);
	shad.uniform4mf("u_Shift", trans);
	shad.uniform_light_source("u_orange", orange);
	shad.uniform_material("u_bronze", bronze);

	if (r >= 1.0f) i = -0.05f;
	if (r <= 0.0f) i = +0.05f;

	if (angle >= 2*PI) angle = 0;

	angle += angle_inc;
	trans = glm::rotate(trans, angle, rot);	
	r += 2*i;

	glfwSwapBuffers(window);
	glfwPollEvents();
  }  
  
  glfwTerminate();
  return 0;
}
