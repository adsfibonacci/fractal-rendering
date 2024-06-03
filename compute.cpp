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

  vbufferlayout layout;
  layout.push({BITTYPE::FLOAT, vertex_size});

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

  material bronze{{0.4f, 0.8f, 0.1f}};
  light orange{{0.8f, 0.7f, 0.6f}};
  
  std::pair<const std::string, const std::string> paths = {
	"shaders/vertex.shader",
	"shaders/fragment.shader"
  };
  shader shad(paths);
  shad.bind();
  shad.uniform_material("u_bronze", bronze);
  shad.uniform_light_source("u_orange", orange);

  float square[4 * vertex_size] = {
	((float)w)/2 - 100.0f, ((float)h)/2 - 100.0f, 0.0f,
	((float)w)/2 - 100.0f, ((float)h)/2 + 100.0f, 0.0f,
	((float)w)/2 + 100.0f, ((float)h)/2 + 100.0f, 0.0f,
	((float)w)/2 + 100.0f, ((float)h)/2 - 100.0f, 0.0f
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
  rend.unload();
  
  camera cam;
  //float inc = +.05f;

  //cam.set_target(glm::vec3((float)w/2, (float)h/2, 0));

  glfwSetWindowUserPointer(window, &cam);
  
  while (!glfwWindowShouldClose(window)) {
	rend.clear();
	glfwSetKeyCallback(window, camera::keyinputs);
	glfwSetScrollCallback(window, camera::scrollinputs);

	//curr_time = static_cast<float>(glfwGetTime());
	rend.draw();
	
	shad.bind();
	shad.uniform4mf("u_view", cam.view());
	shad.uniform_light_source("u_orange", orange);
	shad.uniform_material("u_bronze", bronze);

	//cam.yaw_p(inc);
	//cam.pitch_p(inc);
	//cam.roll_p(inc);
	
	//if (r <= 0.0f) i = +0.05f;

	

	glfwSwapBuffers(window);
	glfwPollEvents();
  }  
  
  glfwTerminate();
  return 0;
}
