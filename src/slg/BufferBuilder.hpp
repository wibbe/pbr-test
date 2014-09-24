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
#include "OpenGL.hpp"

#include "glm/glm.hpp"
#include <vector>

namespace slg {

  /// Helper class for filling a Buffer with data
  template <typename T>
  class BufferBuilder
  {
    public:
      BufferBuilder(Buffer & buffer)
        : m_buffer(buffer)
      { }

      void add(T const& x)
      {
        m_data.push_back(x);
      }

      void vec2(T const& x, T const& y)
      {
        m_data.push_back(x);
        m_data.push_back(y);
      }

      void vec3(T const& x, T const& y, T const& z)
      {
        m_data.push_back(x);
        m_data.push_back(y);
        m_data.push_back(z);
      }

      void vec3(glm::vec3 const& vec)
      {
        m_data.push_back(vec.x);
        m_data.push_back(vec.y);
        m_data.push_back(vec.z);
      }

      void vec4(T const& x, T const& y, T const& z, T const& w)
      {
        m_data.push_back(x);
        m_data.push_back(y);
        m_data.push_back(z);
        m_data.push_back(w);
      }

      void vec4(glm::vec4 const& vec)
      {
        m_data.push_back(vec.x);
        m_data.push_back(vec.y);
        m_data.push_back(vec.z);
        m_data.push_back(vec.w);
      }

      void triangle(T const& a, T const& b, T const& c)
      {
        m_data.push_back(a);
        m_data.push_back(b);
        m_data.push_back(c);
      }

      void quad(T const& a, T const& b, T const& c, T const& d)
      {
        triangle(a, b, c);
        triangle(a, c, d);
      }

      void done()
      {
        m_buffer.upload(&m_data[0], m_data.size() * sizeof(T), GL_STATIC_DRAW);
      }

    private:
      Buffer & m_buffer;
      std::vector<T> m_data;
  };


}