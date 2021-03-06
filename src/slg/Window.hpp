/**
 * Copyright (c) 2012 Daniel Wiberg
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

#ifndef SLG_WINDOW_HPP
#define SLG_WINDOW_HPP

#include <string>
#include "Input.hpp"
#include "glm/glm.hpp"

struct GLFWwindow;

namespace slg {

  /// Used to construct a window with a valid OpenGL context.
  /// Note that there can only exists one window at the time.
  class Window
  {
    public:
      Window(int width, int height, const char * title);
      virtual ~Window();

      void run();

      void setTitle(std::string const& title);

      virtual void resize(int width, int height) { }
      virtual bool update(double dt) { return true; }
      virtual void paint() = 0;

      double time() const { return m_totalTime; }

      Input const& input() const { return m_input; }
      Input & input() { return m_input; }

      glm::mat4 ortho() const;

      GLFWwindow * _glfwWindow() const { return m_window; }

    private:
      GLFWwindow * m_window = nullptr;

      double m_lastTimeStamp = 0.0;
      double m_totalTime = 0.0;

      Input m_input;
  };

}

#endif
