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
  
  void uniform1f(const std::string& name, float pos);
  void uniform4f(const std::string& name, float pos[4]);
  unsigned int get_uniform(const std::string& name);  
  
  unsigned int compile(unsigned int type, const std::string& source);
  unsigned int create(const std::string& vshader, const std::string& fshader);
  std::string read(const std::string& source);
};

#endif //_SHADER
