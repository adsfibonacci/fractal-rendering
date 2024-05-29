#ifndef _SHADER_
#define _SHADER_

#include "syshead.hpp"

class shader {
private:
  std::string m_vpath;
  std::string m_fpath;
  std::unordered_map<std::string, unsigned int> m_cache;
  
  unsigned int m_renderid;  
  
public:
  shader(std::pair<const std::string, const std::string>& p);
  ~shader();

  void bind() const;
  void unbind() const;
  
  void uniform1vf(const std::string& name, const float pos);
  void uniform3vf(const std::string& name, const float* pos);
  void uniform4vf(const std::string& name, const float* pos);
  void uniform4mf(const std::string& name, const glm::mat4& m);

  void uniform_light_source(const std::string& name, const light& l);
  void uniform_material(const std::string& name, const material& m);
  
  unsigned int get_uniform(const std::string& name);
  
  unsigned int compile(unsigned int type, const std::string& source);
  unsigned int create(const std::string& vshader, const std::string& fshader);
  std::string read(const std::string& source);
};

#endif //_SHADER
