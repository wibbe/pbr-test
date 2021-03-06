
#include "OpenGL.hpp"
#include "Shader.hpp"
#include "File.hpp"
#include "Mesh.hpp"

#include <assert.h>
#include <stdio.h>

namespace slg {

  static void showLogInfo(GLuint object,
  								        void (*glGet__iv)(GLuint, GLenum, GLint*),
  								        void (*glGet__InfoLog)(GLuint, GLsizei, GLsizei*, GLchar*))
  {
  	int logLength;
  	char * log;

  	glGet__iv(object, GL_INFO_LOG_LENGTH, &logLength);
  	log = new char[logLength];
  	glGet__InfoLog(object, logLength, NULL, log);
  	fprintf(stderr, "%s", log);

  	delete[] log;
  }

  Shader::Shader()
    : m_program(0),
      m_shaderCount(0)
  {
    m_program = glCreateProgram();

    for (int i = 0; i < MAX_SHADERS; ++i)
      m_shaders[i] = 0;
  }

  Shader::~Shader()
  {
    destroy();
  }

  void Shader::destroy()
  {
    for (int i = 0; i < MAX_SHADERS; ++i)
    {
      if (m_shaders[i])
        glDeleteShader(m_shaders[i]);
      m_shaders[i] = 0;
    }

    if (m_program)
	  	glDeleteProgram(m_program);

	  m_program = 0;
  }

  bool Shader::load(const char * filename, unsigned int type)
  {
    assert(m_shaderCount < MAX_SHADERS);

    int length;
    char * data = 0;

    if (!fileContent(filename, &data, length))
      return false;

    GLuint shader = glCreateShader(type);
	  glShaderSource(shader, 1, (const GLchar **)&data, &length);
	  glCompileShader(shader);

	  delete[] data;

	  int ok;
	  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	  if (!ok)
	  {
	  	fprintf(stderr, "Failed to compile shader: %s\n", filename);
	  	showLogInfo(shader, glGetShaderiv, glGetShaderInfoLog);
	  	destroy();
	  	return false;
	  }

	  m_shaders[m_shaderCount++] = shader;

    return true;
  }

  bool Shader::load2(const char * filename1, const char * filename2, unsigned int type)
  {
    assert(m_shaderCount < MAX_SHADERS);

    int length[2];
    char * data[2];

    if (!fileContent(filename1, &data[0], length[0]))
      return false;

    if (!fileContent(filename2, &data[1], length[1]))
    {
      delete[] data[0];
      return false;
    }

    GLuint shader = glCreateShader(type);
	  glShaderSource(shader, 2, (const GLchar **)data, length);
	  glCompileShader(shader);

	  delete[] data[0];
	  delete[] data[1];

	  int ok;
	  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	  if (!ok)
	  {
	  	fprintf(stderr, "Failed to compile shaders: %s, %s\n", filename1, filename2);
	  	showLogInfo(shader, glGetShaderiv, glGetShaderInfoLog);
	  	destroy();
	  	return false;
	  }

	  m_shaders[m_shaderCount++] = shader;

    return true;
  }

  bool Shader::link()
  {
    for (int i = 0; i <m_shaderCount; ++i)
      glAttachShader(m_program, m_shaders[i]);

    glLinkProgram(m_program);

    int ok;
	  glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
	  if (!ok)
	  {
	  	fprintf(stderr, "Failed to link shader program:\n");
	  	showLogInfo(m_program, glGetProgramiv, glGetProgramInfoLog);
	  	destroy();
	  	return false;
	  }

	  return true;
  }

  void Shader::setupMeshAttributes()
  {
    attribute(Mesh::VERTEX, "inVertex");
    attribute(Mesh::NORMAL, "inNormal");
    attribute(Mesh::UV, "inTexCoord");
    attribute(Mesh::TANGENT, "inTangent");
    attribute(Mesh::BINORMAL, "inBinormal");
  }

  void Shader::bind()
  {
    if (m_program)
      glUseProgram(m_program);
  }

  void Shader::unbind()
  {
    glUseProgram(0);
  }

  void Shader::uniform(const char * name, float x)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniform1f(pos, x);
    }
  }

  void Shader::uniform(const char * name, float x, float y)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniform2f(pos, x, y);
    }
  }

  void Shader::uniform(const char * name, float x, float y, float z)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniform3f(pos, x, y, z);
    }
  }

  void Shader::uniform(const char * name, float x, float y, float z, float w)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniform4f(pos, x, y, z, w);
    }
  }

  void Shader::uniform(const char * name, glm::vec2 const& vec)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniform2f(pos, vec.x, vec.y);
    }
  }

  void Shader::uniform(const char * name, glm::vec3 const& vec)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniform3f(pos, vec.x, vec.y, vec.z);
    }
  }

  void Shader::uniform(const char * name, glm::mat4 const& mat)
  {
    if (m_program)
    {
      GLuint pos = glGetUniformLocation(m_program, name);
      glUniformMatrix4fv(pos, 1, GL_FALSE, &mat[0][0]);
    }
  }

  void Shader::attribute(unsigned int index, const char * name) const
  {
    if (m_program)
      glBindAttribLocation(m_program, index, name);
  }

}
