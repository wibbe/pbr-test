
#include "Camera.h"
#include "OpenGL.h"

#include <memory.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace framework {

  Camera::Camera(float fovy, float near, float far)
    : buffer_(0),
      fovy_(fovy),
      near_(near),
      far_(far),
      shaderData_({{0, 0, -10}, {0, 0, 0}, glm::mat4x4(), glm::mat4x4()})
  {
  }

  Camera::~Camera()
  {
  }

  void Camera::setup()
  {
    // Create uniform buffer, and allocate space for it
    glGenBuffers(1, &buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(shaderData_), 0, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  void Camera::teardown()
  {
    glDeleteBuffers(1, &buffer_);
  }

  void Camera::setViewport(int width, int height)
  {
    shaderData_.projection = glm::perspectiveFov(fovy_, static_cast<float>(width), static_cast<float>(height), near_, far_);
  }

  void Camera::update()
  {
    shaderData_.view = glm::lookAt(shaderData_.eye, shaderData_.center, glm::vec3(0, 1, 0));

    // Copy the updated data
    glBindBuffer(GL_UNIFORM_BUFFER, buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(shaderData_), &shaderData_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

}