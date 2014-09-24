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

#include "CameraControllers.hpp"
#include "Camera.hpp"
#include "Input.hpp"

namespace slg {

  void flyController(Camera & camera, Input & input, double dt)
  {
    if (input.isKeyDown('W'))
      camera.move(10.0 * dt);
    else if (input.isKeyDown('S'))
      camera.move(-10.0 * dt);

    if (input.isKeyDown('D'))
      camera.strafe(5.0 * dt);
    else if (input.isKeyDown('A'))
      camera.strafe(-5.0 * dt);

    if (input.mouseButton(1))
    {
      camera.yaw(input.mouseRelX() * 0.2);
      camera.pitch(input.mouseRelY() * 0.2);
    }
  }

}

