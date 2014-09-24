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

namespace slg {

  class Buffer
  {
    private:
      Buffer(Buffer const& copy) { }
      Buffer const& operator = (Buffer const& copy) { return *this; }

    public:
      Buffer();
      Buffer(int target);
      virtual ~Buffer();

      void bind() const;

      /// Upload data to this buffer
      /// Mode should be one of the following:
      /// * GL_STATIC_DRAW
      /// * GL_DYNAMIC_DRAW
      void upload(const void * data, int len, unsigned int mode);

      int target() const { return m_target; }

    private:
      unsigned int m_id;
      int m_target;
  };

  class VertexBuffer : public Buffer
  {
    public:
      VertexBuffer();
  };

  class IndexBuffer : public Buffer
  {
    public:
      IndexBuffer();
  };

}

