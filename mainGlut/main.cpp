//----------------------------------------------------------------
// Simple example program that creates a GLUT window and draws an image
// as defined by EDL file.
//----------------------------------------------------------------

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/edl_parser.hpp"

#include "openeaagles/graphics/Graphic.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"

// factories
#include "openeaagles/base/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"

#include <GL/glut.h>

#include <string>

// frame rate
const unsigned int frameRate = 20;

oe::glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff
void timerFunc(int)
{
   const double dt = 1.0 / static_cast<double>(frameRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   oe::base::Timer::updateTimers(static_cast<double>(dt));
   oe::graphics::Graphic::flashTimer(static_cast<double>(dt));
   glutDisplay->tcFrame(static_cast<double>(dt));
}

// our class factory
oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;
   if (obj == nullptr) obj = oe::glut::factory(name);
   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

   return obj;
}

// display builder
oe::glut::GlutDisplay* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   const auto pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto glutDisplay = dynamic_cast<oe::glut::GlutDisplay*>(obj);
   if (glutDisplay == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return glutDisplay;
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   std::string configFilename = "glutdisplay.edl";
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   glutDisplay = builder(configFilename);

   // create a display window
   glutDisplay->createWindow();

   // set timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();
   return 0;
}
