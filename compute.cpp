#include "syshead.hpp"
#include "render.hpp"
#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "varray.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "shapes/circle.hpp"
#include "shapes/bandwith.hpp"

int main() {

  if (!glfwInit()) {
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
  
  //float i = +0.05f;
  //float angle_inc = +0.001f;
  
  float curr_time = static_cast<float>(glfwGetTime());;

  //float fragment_color[4] = {0.5f, 0.5f, 0.5f, 1.0f};  
  //float& r = fragment_color[0];
  //float angle = 0.0f;
  //float angle_increment = .05f;
  //float angle = 0.0f;
  //glm::vec3 rot{0.5f, 1.0f, 0.0f};
  //glm::mat4 trans(1.0f);
  //trans = glm::ortho(0.0f, (float)w, 0.0f, (float)h, 0.0f, 1000.0f);
  //trans = glm::rotate(trans, angle, rot);

  std::pair<const std::string, const std::string> paths = {
	"shaders/vertex.shader",
	"shaders/fragment.shader"
  };

  glm::mat4 proj = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1000.0f, 1000.0f);
  camera cam;

  material bronze{{0.4f, 0.8f, 0.1f}};
  light orange{{0.8f, 0.7f, 0.6f}};
  
  shader shad(paths);
  shad.bind();
  //shad.uniform4vf("u_frag_color", fragment_color);
  shad.uniform1vf("u_Time", curr_time);
  shad.uniform4mf("u_view", proj * cam.view());
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

  float tetra_vertices[4* vertex_size] = {
	150.0f, 150.0f, 0.0f,
	450.0f, 150.0f, 0.0f,
	300.0f, 300.0f, -150.0f,
	300.0f, 150.0f, -300.0f
  };
  unsigned int tetra_indices[4 * 3] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 3,
	1, 2, 3
  };
  varray tetra_array;
  vbuffer tetra_vbuffer(tetra_vertices, 4*vertex_size*sizeof(float));
  tetra_array.addbuffer(tetra_vbuffer, layout);
  ibuffer tetra_ibuffer(tetra_indices, 4*3);
  
  std::unordered_map<const ibuffer*, const shader*> tetra_map;
  tetra_map[&tetra_ibuffer] = &shad;

  float square[4 * vertex_size] = {
	400.0f, 400.0f, 0.0f,
	400.0f, 600.0f, 0.0f,
	600.0f, 600.0f, 0.0f,
	600.0f, 400.0f, 0.0f
  };
  unsigned int square_indices[2 * 3] = {
	0, 1, 2,
	2, 3, 0
  };
  varray square_array;
  vbuffer square_vbuffer(square, 4 * vertex_size * sizeof(float));
  ibuffer square_ibuffer(square_indices, 4*2);
  square_array.addbuffer(square_vbuffer, layout);
  std::unordered_map<const ibuffer*, const shader*> square_umap;
  square_umap[&square_ibuffer] = &shad;
  render rend;
  rend.add_mesh(&square_array, square_umap);
  //rend.add_mesh(&tetra_array, tetra_map);
  //rend.add_mesh(b.get_vertex_array(), b.get_mapping());
  //rend.add_mesh(c.get_vertex_array(), c.get_mapping());
  //rend.add_mesh(&va, umap);
  
  rend.unload();

  cam.set_global(glm::vec3(300.0f, 0.0f, 0.0f));

  float inc = +.05f;
      
  while (!glfwWindowShouldClose(window)) {
	rend.clear();

	//curr_time = static_cast<float>(glfwGetTime());
	rend.draw();
	
	shad.bind();
	//shad.uniform4vf("u_frag_color", fragment_color);
	shad.uniform1vf("u_Time", curr_time);
	shad.uniform4mf("u_view", proj * cam.view());
	shad.uniform_light_source("u_orange", orange);
	shad.uniform_material("u_bronze", bronze);

	cam.yaw_p(inc);
	std::cout << cam << std::endl;
	
	//if (r <= 0.0f) i = +0.05f;

	glfwSwapBuffers(window);
	glfwPollEvents();
  }  
  
  glfwTerminate();
  return 0;
}
