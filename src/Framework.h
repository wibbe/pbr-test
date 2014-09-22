
#pragma once

#include <memory>
#include <string>

namespace framework {

  struct Config
  {
    int windowWidth = 1280;
    int windowHeight = 720;
    double fps = 60.0;
    std::string title = "Framework";
  };

  class Framework
  {
    public:
      Framework();
      virtual ~Framework();

      int run(Config const& config);
      void getWindowSize(int & width, int & height);

      virtual void setup() { }
      virtual void teardown() { }
      virtual void update(double dt) { }
      virtual void paint(double dt) { }

    private:
      class Private;
      std::unique_ptr<Private> d_;
  };



  void log(const char * message, ...);
  void error(const char * format, ...);

  extern std::unique_ptr<Framework> allocate(Config & config);
}

#define DEFINE_APPLICATION(Type) \
  namespace framework { \
    std::unique_ptr<Framework> allocate(framework::Config & config) { return std::unique_ptr<Framework>(new Type(config)); } \
  } \
