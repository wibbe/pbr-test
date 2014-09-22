
#include "Program.h"
#include "OpenGL.h"

namespace framework {

  Program::Program()
  {
  }

  void Program::setup()
  {
    if (handle_ != 0)
    {
      handle_ = glCreateProgram();
    }
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

}