

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "OpenGL.h"
#include "Framework.h"

namespace framework {

  void fw_errorCallback(int error, const char * description)
  {
    fprintf(stderr, "ERROR(%d): %s\n", error, description);
  }

  void log(const char * format, ...)
  {
    static const int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    va_end(args);

    fprintf(stderr, "Info: %s\n", buffer);
  }

  void error(const char * format, ...)
  {
    static const int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    va_end(args);

    fprintf(stderr, "Error: %s\n", buffer);
  }


  class Framework::Private
  {
    public:
      GLFWwindow * window_ = nullptr;
  };

  Framework::Framework()
    : d_(new Framework::Private())
  {
  }

  Framework::~Framework()
  {
  }

  int Framework::run(Config const& config)
  {
    log("Initializing GLFW...");
    if (!glfwInit())
      return 1;

    glfwSetErrorCallback(fw_errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    log("Creating window...");
    d_->window_ = glfwCreateWindow(config.windowWidth, config.windowHeight, config.title.c_str(), NULL, NULL);
    if (!d_->window_)
    {
      glfwTerminate();
      return 1;
    }

    glfwMakeContextCurrent(d_->window_);

    log("Initializing GLEW..");

    glewExperimental = GL_TRUE;
    const GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK)
    {
      error("Could not initialize glew %s", glewGetErrorString(glewErr));
      glfwTerminate();
      return 1;
    }
    else
      log("Using GLEW %s", glewGetString(GLEW_VERSION));

    { // Display some information about the OpenGL version we are running
      const GLubyte * renderer = glGetString(GL_RENDERER);
      const GLubyte * vendor = glGetString(GL_VENDOR);
      const GLubyte * version = glGetString(GL_VERSION);
      const GLubyte * glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

      GLint major, minor;
      glGetIntegerv(GL_MAJOR_VERSION, &major);
      glGetIntegerv(GL_MINOR_VERSION, &minor);

      log("GL Vendor    = %s", vendor);
      log("GL Renderer  = %s", renderer);
      log("GL Version (string)  = %s", version);
      log("GL Version (integer) = %d.%d", major, minor);
      log("GLSL Version = %s", glslVersion);
    }

    setup();

    double timeStamp = glfwGetTime();
    double accumulator = 0.0;
    const double frameTime = 1.0 / config.fps;

    while (!glfwWindowShouldClose(d_->window_))
    {
      const double currentTime = glfwGetTime();
      const double dt = currentTime - timeStamp;
      timeStamp = currentTime;

      accumulator += dt;
      while (accumulator >= frameTime)
      {
        update(frameTime);
        accumulator -= frameTime;
      }

      paint(dt);

      glfwSwapBuffers(d_->window_);
      glfwPollEvents();
    }

    teardown();

    glfwDestroyWindow(d_->window_);
    glfwTerminate();

    return 0;
  }


  void Framework::getWindowSize(int & width, int & height)
  {
    if (d_->window_)
      glfwGetFramebufferSize(d_->window_, &width, &height);
    else
    {
      width = 0;
      height = 0;
    }
  }
}

int main(int argc, char * argv[])
{
  framework::Config config;
  std::unique_ptr<framework::Framework> app = framework::allocate(config);
  return app->run(config);
}
