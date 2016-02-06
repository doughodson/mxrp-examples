
#include "factory.h"

#include "openeaagles/basic/Object.h"

#include "TestStateMachine01.h"
#include "TestStateMachine02.h"
#include "TestStateMachine03.h"
#include "TestStateMachine04.h"
#include "TestStateMachine04A.h"
#include "TestStateMachine04B.h"
#include "TestStateMachine04C.h"

#include "openeaagles/basic/factory.h"

#include <cstring>

namespace oe {
namespace test {

basic::Object* factory(const char* name)
{
    basic::Object* obj = nullptr;

    // Test #1
    if ( std::strcmp(name, TestStateMachine01::getFactoryName()) == 0 ) {
        obj = new TestStateMachine01();
    }

    // Test #2
    else if ( std::strcmp(name, TestStateMachine02::getFactoryName()) == 0 ) {
        obj = new TestStateMachine02();
    }

    // Test #3
    else if ( std::strcmp(name, TestStateMachine03::getFactoryName()) == 0 ) {
        obj = new TestStateMachine03();
    }

    // Test #4
    else if ( std::strcmp(name, TestStateMachine04::getFactoryName()) == 0 ) {
        obj = new TestStateMachine04();
    }
    else if ( std::strcmp(name, TestStateMachine04A::getFactoryName()) == 0 ) {
        obj = new TestStateMachine04A();
    }
    else if ( std::strcmp(name, TestStateMachine04B::getFactoryName()) == 0 ) {
        obj = new TestStateMachine04B();
    }
    else if ( std::strcmp(name, TestStateMachine04C::getFactoryName()) == 0 ) {
        obj = new TestStateMachine04C();
    }

    // OpenEaagles packages
    if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

}
}