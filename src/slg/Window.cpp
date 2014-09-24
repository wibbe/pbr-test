
#include "Window.hpp"
#include "Log.hpp"
#include "OpenGL.hpp"
#include "Math.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace slg {

  // -- Callbacks --

  void mouseButton(GLFWwindow * window, int button, int state, int mod)
  {
    Window * currentWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (currentWindow)
      currentWindow->input().setMouseButton(button, state == GLFW_PRESS);
  }

  void mousePosition(GLFWwindow * window, double x, double y)
  {
    Window * currentWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (currentWindow)
      currentWindow->input().setMousePos(x, y);
  }

  void windowResized(GLFWwindow * window, int width, int height)
  {
    Window * currentWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (currentWindow)
      currentWindow->resize(width, height);
  }

  // -- Window --

  Window::Window(int width, int height, const char * title)
    : m_input(*this)
  {
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(m_window);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetMouseButtonCallback(m_window, &mouseButton);
    glfwSetCursorPosCallback(m_window, &mousePosition);
    glfwSetFramebufferSizeCallback(m_window, &windowResized);

    log("Initializing GLEW..");

    glewExperimental = GL_TRUE;
    const GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK)
    {
      error("Could not initialize glew %s", glewGetErrorString(glewErr));
      glfwDestroyWindow(m_window);
      glfwTerminate();
      exit(1);
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


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    for (int texUnit = 0; texUnit < 4; ++texUnit)
    {
      glActiveTexture(GL_TEXTURE0 + texUnit);
      glEnable(GL_TEXTURE_2D);
    }

    glActiveTexture(GL_TEXTURE0);
  }

  Window::~Window()
  {
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  void Window::run()
  {
    glfwSetTime(0.0);
    m_lastTimeStamp = 0.0;
    m_totalTime = 0.0;

    // Call resize before we start
    {
      int width, height;
      glfwGetFramebufferSize(m_window, &width, &height);
      resize(width, height);
    }

    bool running = true;
    double accumulator = 0.0;
    const double frameTime = 1.0 / 60.0;

    while (!glfwWindowShouldClose(m_window) && running)
    {
      const double timeStamp = glfwGetTime();
      const double dt = timeStamp - m_lastTimeStamp;
      m_lastTimeStamp = timeStamp;

      m_totalTime += dt;
      accumulator += dt;

      while (running && accumulator >= frameTime)
      {
        running = update(frameTime);
        accumulator -= frameTime;
      }

      paint();

      glfwSwapBuffers(m_window);
      glfwPollEvents();
    }
  }

  void Window::setTitle(std::string const& title)
  {
    glfwSetWindowTitle(m_window, title.c_str());
  }

  glm::mat4 Window::ortho() const
  {
    int width;
    int height;
    glfwGetFramebufferSize(m_window, &width, &height);

    return glm::ortho(0.0f, (float)width, (float)height, (float)0.0f);
  }

}
