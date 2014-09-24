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

#include "Input.hpp"
#include "Window.hpp"
#include "OpenGL.hpp"

#include <cassert>

namespace slg {

  Input::Input(Window & window)
    : m_window(window),
      m_mouseX(0),
      m_mouseY(0),
      m_mouseRelX(0),
      m_mouseRelY(0)
  {
    for (int i = 0; i < MOUSE_BUTTON_COUNT; ++i)
      m_mouseButtons[i] = false;
  }

  int Input::mouseRelX()
  {
    int val = m_mouseRelX;
    m_mouseRelX = 0;
    return val;
  }

  int Input::mouseRelY()
  {
    int val = m_mouseRelY;
    m_mouseRelY = 0;
    return val;
  }

  bool Input::mouseButton(int button) const
  {
    assert(button < MOUSE_BUTTON_COUNT);
    return m_mouseButtons[button];
  }

  bool Input::isKeyDown(int key) const
  {
    return glfwGetKey(m_window._glfwWindow(), key);
  }

  void Input::setMousePos(int x, int y)
  {
    m_mouseRelX = x - m_mouseX;
    m_mouseRelY = y - m_mouseY;
    m_mouseX = x;
    m_mouseY = y;
  }

  void Input::setMouseButton(int button, bool down)
  {
    m_mouseButtons[button] = down;
  }

}
