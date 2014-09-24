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

#include "glm/glm.hpp"

namespace slg {

  class Window;

  class Input
  {
    public:
      static const int MOUSE_BUTTON_COUNT = 3;

    public:
      Input(Window & window);

      int mouseX() const { return m_mouseX; }
      int mouseY() const { return m_mouseY; }
      int mouseRelX();
      int mouseRelY();

      glm::ivec2 mousePosition() const { return glm::ivec2(m_mouseX, m_mouseY); }

      bool mouseButton(int button) const;
      bool isKeyDown(int key) const;

      void setMousePos(int x, int y);
      void setMouseButton(int button, bool down);

    private:
      Window & m_window;

      int m_mouseX;
      int m_mouseY;
      int m_mouseRelX;
      int m_mouseRelY;
      bool m_mouseButtons[MOUSE_BUTTON_COUNT];
  };

}
