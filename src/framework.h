
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// Functions that needs to be implemented
void setup();
void update(double dt);
void paint(double dt);

/// API

void getWindowSize(int * width, int * height);


#endif // FRAMEWORK_H


#ifdef FRAMEWORK_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <stdio.h>

#ifndef FRAMEWORK_WIDTH
  #define FRAMEWORK_WIDTH 1280
#endif

#ifndef FRAMEWORK_HEIGHT
  #define FRAMEWORK_HEIGHT 720
#endif

#ifndef FRAMEWORK_TITLE
  #define FRAMEWORK_TITLE "OpenGL Framework"
#endif

#ifndef FRAMEWORK_FPS 
  #define FRAMEWORK_FPS 60.0
#endif

GLFWwindow * window_ = NULL;

void fw_errorCallback(int error, const char * description)
{
  fprintf(stderr, "ERROR(%d): %s\n", error, description);
}

void getWindowSize(int * width, int * height)
{
  if (window_)
    glfwGetFramebufferSize(window_, width, height);
  else
  {
    *width = 0;
    *height = 0;
  }
}

int main(int argc, char * argv[])
{
  if (!glfwInit())
    return 1;

  glfwSetErrorCallback(fw_errorCallback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window_ = glfwCreateWindow(1280, 720, "PBR Test", NULL, NULL);
  if (!window_)
  {
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window_);

  setup();

  double timeStamp = glfwGetTime();
  double accumulator = 0.0;
  const double frameTime = 1.0 / FRAMEWORK_FPS;

  while (!glfwWindowShouldClose(window_))
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

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  glfwDestroyWindow(window_);
  glfwTerminate();

  return 0;
}

#endif // FRAMEWORK_IMPLEMENTATION