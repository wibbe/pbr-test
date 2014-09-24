/**
 * Copyright (c) 2014 Daniel Wiberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Mesh.hpp"
#include "MeshHelpers.hpp"
#include "OpenGL.hpp"

#include <openctm.h>

namespace slg {

  Mesh::Mesh()
  {
  }

  Mesh::~Mesh()
  {
    destroy();
  }

  void Mesh::destroy()
  {
    glDeleteBuffers(BUFFER_COUNT, buffers_);
    glDeleteVertexArrays(1, &vao_);

    vao_ = 0;
  }

  bool Mesh::load(const char * filename, bool computeTangents)
  {
    CTMcontext context = ctmNewContext(CTM_IMPORT);
    bool result = false;

    ctmLoad(context, filename);
    if (ctmGetError(context) == CTM_NONE)
    {
      result = true;

      const CTMuint triangleCount = ctmGetInteger(context, CTM_TRIANGLE_COUNT);
      const CTMuint vertCount = ctmGetInteger(context, CTM_VERTEX_COUNT);
      const CTMfloat * vertices = ctmGetFloatArray(context, CTM_VERTICES);
      const CTMfloat * normals = ctmGetFloatArray(context, CTM_NORMALS);
      const CTMfloat * texCoord0 = ctmGetFloatArray(context, CTM_UV_MAP_1);
      const CTMuint * indices = ctmGetIntegerArray(context, CTM_INDICES);

      begin();
      add(Mesh::VERTEX, GL_FLOAT, 3, vertices, sizeof(CTMfloat) * vertCount * 3);
      add(Mesh::NORMAL, GL_FLOAT, 3, normals, sizeof(CTMfloat) * vertCount * 3);
      add(Mesh::UV, GL_FLOAT, 3, texCoord0, sizeof(CTMfloat) * vertCount * 2);

      if (computeTangents)
      {

      }

      add(Mesh::INDICIES, 0, 0, indices, sizeof(CTMuint) * triangleCount);
      end(triangleCount);
    }

    ctmFreeContext(context);
    return result;
  }

  Mesh & Mesh::begin()
  {
    destroy();
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    return *this;
  }

  void Mesh::end(unsigned indexCount)
  {
    indexCount_ = indexCount;
    glBindVertexArray(0);
  }

  Mesh & Mesh::add(Attributes attrib, unsigned type, unsigned elemCount, const void * data, size_t size)
  {
    assert(vao_ != 0 && attrib < BUFFER_COUNT && buffers_[attrib] == 0);

    glGenBuffers(1, &buffers_[attrib]);

    if (attrib == INDICIES)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_[attrib]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    else
    {
      glBindBuffer(GL_ARRAY_BUFFER, buffers_[attrib]);
      glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
      glEnableVertexAttribArray(attrib);
      glVertexAttribPointer(attrib, elemCount, type, GL_FALSE, 0, 0);
    }

    return *this;
  }

  void Mesh::draw() const
  {
    assert(vao_ != 0);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, indexCount_);
    glBindVertexArray(0);
  }

}
