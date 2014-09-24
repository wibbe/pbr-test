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

#include "Buffer.hpp"
#include "OpenGL.hpp"

#include <assert.h>

namespace slg {

  Buffer::Buffer()
    : m_id(0),
      m_target(0)
  { }

  Buffer::Buffer(int target)
    : m_id(0),
      m_target(target)
  {
    glGenBuffers(1, &m_id);
  }

  Buffer::~Buffer()
  {
    glDeleteBuffers(1, &m_id);
  }

  void Buffer::bind() const
  {
    glBindBuffer(m_target, m_id);
  }

  void Buffer::upload(const void * data, int len, unsigned int mode)
  {
    assert(m_id != 0);

    glBindBuffer(m_target, m_id);
    glBufferData(m_target, len, data, mode);
  }

  // -- VertexBuffer --

  VertexBuffer::VertexBuffer()
    : Buffer(GL_ARRAY_BUFFER)
  {
  }

  // -- IndexBuffer --

  IndexBuffer::IndexBuffer()
    : Buffer(GL_ELEMENT_ARRAY_BUFFER)
  {
  }
}
