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
  shader(const std::string& vpath, const std::string& fpath);
  ~shader();

  void bind() const;
  void unbind() const;
  
  void uniform1vf(const std::string& name, float pos);
  void uniform4vf(const std::string& name, float pos[4]);
  void uniform4mf(const std::string& name, glm::mat4& m);
  unsigned int get_uniform(const std::string& name);  
  
  unsigned int compile(unsigned int type, const std::string& source);
  unsigned int create(const std::string& vshader, const std::string& fshader);
  std::string read(const std::string& source);
};

#endif //_SHADER
