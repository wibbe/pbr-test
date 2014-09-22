
#define FRAMEWORK_WIDTH 1280
#define FRAMEWORK_HEIGHT 720
#define FRAMEWORK_TITLE "PBR Test"

#include "Framework.h"
#include "Mesh.h"
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
      dagger_ = std::make_shared<framework::Mesh>();
      if (!dagger_->load("../data/dagger.ctm"))
        framework::error("Could not load mesh data/dagger.ctm");
    }

    void teardown()
    {
      dagger_.reset();
    }

    void update(double dt)
    {

    }

    void paint(double dt)
    {
      int width, height;
      getWindowSize(width, height);

      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);

      dagger_->draw();
    }

  private:
    std::shared_ptr<framework::Mesh> dagger_;
};

DEFINE_APPLICATION(PBRTest);