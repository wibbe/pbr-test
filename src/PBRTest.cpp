
#define FRAMEWORK_WIDTH 1280
#define FRAMEWORK_HEIGHT 720
#define FRAMEWORK_TITLE "PBR Test"

#include "Framework.h"
#include "Mesh.h"
#include "Camera.h"
#include "OpenGL.h"

#include "fpumath.h"

class PBRTest : public framework::Framework
{
  public:
    PBRTest(framework::Config & config)
    {
      config.windowWidth = 1280;
      config.windowHeight = 720;
      config.title = "PBR Test";
    }

    void setup()
    {
      camera_.setup();

      if (!dagger_.load("../data/Dagger.ctm"))
        framework::error("Could not load mesh data/Dagger.ctm");
    }

    void teardown()
    {
      camera_.teardown();
      dagger_.teardown();
    }

    void update(double dt)
    {

    }

    void paint(double dt)
    {
      int width, height;
      getWindowSize(width, height);

      camera_.update();

      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      dagger_.draw();
    }

  private:
    framework::Mesh dagger_;
    framework::Camera camera_ = framework::Camera(M_PI * 0.8, 1.0, 1000.0);
};

DEFINE_APPLICATION(PBRTest);