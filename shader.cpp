#include "shader.hpp"

shader::shader(const std::string& vpath, const std::string& fpath) : m_vpath(vpath), m_fpath(fpath) {
  std::string vert = read(vpath);
  std::string frag = read(fpath);
  m_renderid = create(vert, frag);  
}

shader::~shader() {
  GLCall(glDeleteProgram(m_renderid));
}

void shader::bind() const {
  GLCall(glUseProgram(m_renderid));
}

void shader::unbind() const {
  GLCall(glUseProgram(0));
}

void shader::uniform1f(const std::string& name, float pos) {
  GLCall(glUniform1f(get_uniform(name), pos));
}

void shader::uniform4f(const std::string& name, float pos[4]) {
  GLCall(glUniform4f(get_uniform(name), pos[0], pos[1], pos[2], pos[3]));
}

unsigned int shader::get_uniform(const std::string& name) {
  if(m_cache.find(name) != m_cache.end()) {
	return m_cache[name];
  }
  GLCall(unsigned int location = glGetUniformLocation(m_renderid, name.c_str()));
  if(location == UINT_MAX) {
	std::cout << "Warning: " << name << " doesn't exist" << std::endl;
  }
  m_cache[name] = location;
  return location;
}

unsigned int shader::compile(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  glCompileShader(id);

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if(result == GL_FALSE) {
	int length;
	GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

	char* message = new char[length];
	
	//char* message = (char*) alloca(length * sizeof(char));
	GLCall(glGetShaderInfoLog(id, length, &length, message));
	std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
	std::cout << message << std::endl;

	GLCall(glDeleteShader(id));
	return 0;
  }
  return id;
}

unsigned int shader::create(const std::string& vshader, const std::string& fshader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compile(GL_VERTEX_SHADER, vshader);
  unsigned int fs = compile(GL_FRAGMENT_SHADER, fshader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

std::string shader::read(const std::string& source) {
  std::ifstream ifile(source);  
  std::stringstream shader;

  if(!ifile.is_open()) {
	std::cerr << "Error in shader path " << source << std::endl;
	return "";
  }

  shader << ifile.rdbuf();
  return shader.str();
}
