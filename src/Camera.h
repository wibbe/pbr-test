
#pragma once

#include "ContextObject.h"
#include <glm/glm.hpp>

namespace framework {

  class Camera : public ContextObject
  {
    public:
      Camera(float fovy, float near, float far);
      ~Camera();

      void setup();
      void teardown();

      void setViewport(int width, int height);
      void update();

      unsigned uniformBuffer() const { return buffer_; }

    private:
      unsigned buffer_;

      float fovy_;
      float near_;
      float far_;

      struct ShaderData
      {
        glm::vec3 eye;
        glm::vec3 center;

        glm::mat4x4 view;
        glm::mat4x4 projection;
      } shaderData_;
  };

}