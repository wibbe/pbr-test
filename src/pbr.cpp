
#define FRAMEWORK_WIDTH 1280
#define FRAMEWORK_HEIGHT 720
#define FRAMEWORK_TITLE "PBR Test"

#define FRAMEWORK_IMPLEMENTATION
#include "framework.h"

void setup()
{

}

void update(double dt)
{

}

void paint(double dt)
{
  int width, height;
  getWindowSize(&width, &height);

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);
}