
#pragma once

#include "ContextObject.h"

namespace framework {

  class Program : public ContextObject
  {
    public:
      Program();

      void setup();
      void teardown();

    private:
      unsigned handle_ = 0;
      bool linked_ = false;
  };

}