
#include "Application.h"
#include "FoxDisplay.h"
#include "FoxStation.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/graphics/Graphic.h"
#include "openeaagles/base/util/system.h"

// display refresh rate (Hz)
static const FXuint DRAW_FRAME_RATE = 50;

// Message Map
FXDEFMAP(Application) AppMap[] = {
  //_Message_Type__________ID______________________________________Message_Handler__________________
  FXMAPFUNC(SEL_TIMEOUT,   Application::ID_TIMEOUT,                Application::onTimeout),
};

// Macro for the Application class hierarchy implementation
FXIMPLEMENT(Application,FXApp,AppMap,ARRAYNUMBER(AppMap))

Application::Application(const FXString& name, const FXString& vendor) : FXApp(name, vendor)
{
   station = nullptr;
}

Application::~Application()
{
   if (station!=nullptr) {
      station->unref();
      station = nullptr;
   }
}

void Application::init(int& argc, char** argv, bool connect)
{
   FXApp::init(argc, argv, connect);

   // schedule a timer for display refresh
   const double dt0 = 1.0 / static_cast<double>(DRAW_FRAME_RATE);
   const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   addTimeout(this, ID_TIMEOUT, millis);
}

// when we timeout
long Application::onTimeout(FXObject*, FXSelector, void*)
{
   // ---
   // reschedule the display refresh timer
   // ---
   const double dt0 = 1.0/static_cast<double>(DRAW_FRAME_RATE);
   const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   addTimeout(this, ID_TIMEOUT, millis);

   // ---
   // compute delta time
   // ---
   const double time = oe::base::getComputerTime(); // Current time
   static double time0 = time;      // N-1 time
   double dt = time - time0;
   if (dt < 0) {
      dt = 0;
   }
   time0 = time;

   // ---
   // update station data (background thread)
   // and get the current status display data.
   // ---
   station->updateData(static_cast<double>(dt));

   // ---
   // draw the FOX displays
   // ---
   if (station->getMainDisplay() != nullptr) {
      station->getMainDisplay()->drawIt();
   }
   return 1;
}

void Application::setStation(FoxStation* x)
{
   if (station != nullptr) {
      station->unref();
   }
   station = x;
   station->ref();
}

FoxStation* Application::getStation()
{
   return station;
}