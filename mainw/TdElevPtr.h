//------------------------------------------------------------------------------
// Class: TdElevPtr
//
// Description: Test Display Elevation Pointer
//------------------------------------------------------------------------------
#ifndef __TdElevPtr_H__
#define __TdElevPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace MainW {

class TdElevPtr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TdElevPtr,BasicGL::Graphic)

public:
    TdElevPtr();

    virtual bool event(const int event, Basic::Object* const obj = 0);
    virtual void draw();

    //event handler macro functions
    virtual bool onUpdateValue(const Basic::Number* const ouvobj);

private:
    LCreal      elev;
};

} // End MainW namespace
} // End Eaagles namespace

#endif
