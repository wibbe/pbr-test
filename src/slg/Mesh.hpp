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

#pragma once

#include "Buffer.hpp"
#include "Shader.hpp"

#include <vector>

namespace slg {

  class Mesh
  {
    public:
      enum Attributes
      {
        VERTEX,
        NORMAL,
        UV,
        TANGENT,
        BINORMAL,
        INDICIES,
        BUFFER_COUNT
      };

    public:
      Mesh();
      ~Mesh();

      void destroy();
      bool load(const char * filename, bool computeTangents = false);

      Mesh & begin();
      void end(unsigned indexCount);

      Mesh & add(Attributes attrib, unsigned type, unsigned elemCount, const void * data, size_t size);

      template <typename T>
      Mesh & add(Attributes attrib, unsigned type, unsigned elemCount, std::vector<T> const& data)
      {
        return add(attrib, type, elemCount, &data[0], data.size() * sizeof(T));
      }

      void draw() const;

    private:
      unsigned vao_ = 0;
      unsigned buffers_[BUFFER_COUNT] = { 0 };
      unsigned indexCount_ = 0;
  };

}
