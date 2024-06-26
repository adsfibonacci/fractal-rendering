#include "shader.hpp"

shader::shader(std::pair<const std::string, const std::string>& p) : m_vpath(p.first), m_fpath(p.second) {
  std::string vert = read(p.first);
  std::string frag = read(p.second);
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

void shader::uniform1vf(const std::string& name, const float pos) {
  GLCall(glUniform1f(get_uniform(name), pos));
}
void shader::uniform3vf(const std::string& name, const float* pos) {
  GLCall(glUniform3fv(get_uniform(name), 1, pos));
}
void shader::uniform4vf(const std::string& name, const float* pos) {
  GLCall(glUniform4fv(get_uniform(name), 1, pos));
}
void shader::uniform4mf(const std::string& name, const glm::mat4& m) {
  GLCall(glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, &m[0][0]));
}

void shader::uniform_light_source(const std::string& name, const light &l) {
  //uniform3vf(name + ".pos", l.pos);
  uniform3vf(name + ".col", l.col);
  //uniform3vf(name + ".amb", l.amb);
  //uniform3vf(name + ".dif", l.dif);
  //uniform3vf(name + ".spc", l.spc);
}
void shader::uniform_material(const std::string& name, const material &m) {
  uniform3vf(name + ".col", m.col);
  //uniform3vf(name + ".amb", m.amb);
  //uniform3vf(name + ".dif", m.dif);
  //uniform3vf(name + ".spc", m.spc);
  //uniform1vf(name + ".ref", m.ref);
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

  GLCall(glAttachShader(program, fs));
  GLCall(glAttachShader(program, vs));
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
