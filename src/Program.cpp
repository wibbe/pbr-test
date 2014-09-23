
#include "Program.h"
#include "Framework.h"
#include "OpenGL.h"

#include <vector>
#include <stdio.h>

namespace framework {

  Program::Program()
  {
  }

  void Program::teardown()
  {
    if (handle_ != 0)
    {
      glDeleteProgram(handle_);
      handle_ = 0;
      linked_ = false;
    }
  }

  static GLenum toGL(Program::ShaderType type)
  {
    switch (type)
    {
      case Program::VERTEX:
        return GL_VERTEX_SHADER;

      case Program::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    }
  }

  bool Program::compileFile(ShaderType type, std::string const& filename)
  {
    if (handle_ == 0)
      handle_ = glCreateProgram();

    std::vector<char> data;
    if (FILE * fp = fopen(filename.c_str(), "r"))
    {
      char buf[1024];
      while (size_t len = fread(buf, 1, sizeof(buf), fp))
        data.insert(data.end(), buf, buf + len);

      data.push_back('\0');
      fclose(fp);
    }

    const GLenum shaderType = toGL(type);
    const GLchar * codeArray[] = { &data[0] };

    // Create and compile the shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, codeArray, NULL);
    glCompileShader(shader);

    // Vertify that the shader is valid
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
      error("Failed to compile shader '%s':", filename.c_str());
      GLint logLen;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
      if (logLen > 0)
      {
        char * log = new char[logLen];
        GLsizei written;
        glGetShaderInfoLog(shader, logLen, &written, log);
        error("%s", log);
        delete[] log;

        return false;
      }
    }

    return true;
  }

  bool Program::compileSource(ShaderType type, std::string const& code)
  {
    return false;
  }

  bool Program::link()
  {
  }

}