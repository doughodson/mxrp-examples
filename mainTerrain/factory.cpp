
#include "factory.hpp"

#include "mxrp/base/Object.hpp"

#include "Display.hpp"

#include "mxrp/terrain/factory.hpp"
#include "mxrp/graphics/factory.hpp"
#include "mxrp/gui/glut/factory.hpp"
#include "mxrp/base/factory.hpp"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == Display::getFactoryName() ) {
        obj = new Display();
    }

    if (obj == nullptr) obj = oe::terrain::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}
