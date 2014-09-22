
#pragma once

#include <string>

namespace framework {

  class Mesh
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

      bool load(std::string const& filename);

      void draw() const;

    private:
      unsigned vao_ = 0;
      unsigned buffers_[BUFFER_COUNT] = { 0 };
      unsigned triangleCount_ = 0;
  };

}