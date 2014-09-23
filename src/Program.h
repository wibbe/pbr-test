
#pragma once

#include "ContextObject.h"

#include <string>

namespace framework {

  class Program : public ContextObject
  {
    public:
      enum ShaderType
      {
        VERTEX,
        FRAGMENT
      };

    public:
      Program();

      void teardown();

      bool compileFile(ShaderType type, std::string const& filename);
      bool compileSource(ShaderType type, std::string const& code);

      bool link();

    private:
      unsigned handle_ = 0;
      bool linked_ = false;
  };

}