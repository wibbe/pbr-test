
#pragma once

#include "ContextObject.h"
#include <string>

namespace framework {

  class Mesh : public ContextObject
  {
      enum Buffer
      {
        VERTICES,
        NORMALS,
        UV_MAP_0,
        INDICES,
        BUFFER_COUNT
      };


    public:
      Mesh();
      ~Mesh();

      void teardown();

      bool load(std::string const& filename);

      void draw() const;

    private:
      unsigned vao_ = 0;
      unsigned buffers_[BUFFER_COUNT] = { 0 };
      unsigned triangleCount_ = 0;
  };

}