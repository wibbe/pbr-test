
#include <openctm.h>
#include <stdlib.h>
#include <cassert>

#include "Mesh.h"
#include "OpenGL.h"

namespace framework {

  Mesh::Mesh()
  {
  }

  Mesh::~Mesh()
  {
  }

  void Mesh::teardown()
  {
    glDeleteBuffers(BUFFER_COUNT, buffers_);
    glDeleteVertexArrays(1, &vao_);
  }

  bool Mesh::load(std::string const& filename)
  {
    CTMcontext context = ctmNewContext(CTM_IMPORT);

    bool result = false;

    ctmLoad(context, filename.c_str());
    if (ctmGetError(context) == CTM_NONE)
    {
      result = true;

      triangleCount_ = ctmGetInteger(context, CTM_TRIANGLE_COUNT);
      const CTMuint vertCount = ctmGetInteger(context, CTM_VERTEX_COUNT);
      const CTMfloat * vertices = ctmGetFloatArray(context, CTM_VERTICES);
      const CTMfloat * normals = ctmGetFloatArray(context, CTM_NORMALS);
      const CTMfloat * texCoord0 = ctmGetFloatArray(context, CTM_UV_MAP_1);
      const CTMuint * indices = ctmGetIntegerArray(context, CTM_INDICES);

      glGenVertexArrays(1, &vao_);
      glBindVertexArray(vao_);

      glGenBuffers(BUFFER_COUNT, buffers_);

      glBindBuffer(GL_ARRAY_BUFFER, buffers_[VERTICES]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(CTMfloat) * vertCount * 3, vertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(VERTICES);
      glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glBindBuffer(GL_ARRAY_BUFFER, buffers_[NORMALS]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(CTMfloat) * vertCount * 3, normals, GL_STATIC_DRAW);
      glEnableVertexAttribArray(NORMALS);
      glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glBindBuffer(GL_ARRAY_BUFFER, buffers_[UV_MAP_0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(CTMfloat) * vertCount * 2, texCoord0, GL_STATIC_DRAW);
      glEnableVertexAttribArray(UV_MAP_0);
      glVertexAttribPointer(UV_MAP_0, 2, GL_FLOAT, GL_FALSE, 0, 0);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_[INDICES]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CTMuint) * triangleCount_, indices, GL_STATIC_DRAW);

      glBindVertexArray(0);
    }

    ctmFreeContext(context);
    return result;
  }

  void Mesh::draw() const
  {
    assert(vao_ != 0);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, triangleCount_);
    glBindVertexArray(0);
  }

}
