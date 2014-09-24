
#ifndef SLG_FLY_CONTROLLER_HPP
#define SLG_FLY_CONTROLLER_HPP

namespace slg {

  class Camera;
  class Input;

  void flyController(Camera & camera, Input & input, double dt);

}

#endif

