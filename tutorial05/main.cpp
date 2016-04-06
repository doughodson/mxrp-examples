
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/PairStream.h"
#include "openeaagles/base/Color.h"
#include "openeaagles/base/parser.h"
#include "openeaagles/base/String.h"

// factories
#include "openeaagles/base/factory.h"

#include "MyObj.h"

namespace oe {
namespace tutorial {

MyObj* myObj = nullptr;

// our class factory
base::Object* factory(const char* const name)
{
   base::Object* obj = nullptr;

   // look in application's classes
   if ( std::strcmp(name, MyObj::getFactoryName()) == 0 ) {
      obj = new MyObj;
   }
   // look in base classes
   if (obj == nullptr) obj = base::factory(name);
   return obj;
}

// MyObj builder
MyObj* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   base::Object* obj = base::edlParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   MyObj* myObj = dynamic_cast<MyObj*>(obj);
   if (myObj == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return myObj;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "file0.edl";

   // build my object
   myObj = builder(configFilename);

   // print out some color information
   const base::PairStream* colorTable = myObj->getColorTable();
   if (colorTable != nullptr) {
//    Pair* p = colorTable->findByName("green");
      const base::Identifier* id = myObj->getTextColor();
      if (id != nullptr) {
         const base::Pair* p = colorTable->findByName(id->getString());
         if (p != nullptr) {
            std::cout << "Text color: " << id->getString();
            const base::Color* color = dynamic_cast<const base::Color*>(p->object());
            if (color != nullptr) {
               std::cout << " Red: "   << color->red();
               std::cout << " Green: " << color->green();
               std::cout << " Blue: "  << color->blue();
            }
            std::cout << std::endl;
         } else {
            std::cout << "Text color not found\n" << std::endl;
         }
      }
   }

   // print out vector information
   const base::List* vector = myObj->getVector();
   if (vector != nullptr) {
      int numValues = vector->entries();
      int* values = new int[numValues];
      int n = vector->getNumberList(values,numValues);
      std::cout << "Vector: ";
      std::cout << "# Numeric Entries: " << n << " Values: ";
      for (int i=0; i < n; i++)
         std::cout << values[i] << " ";
      std::cout << std::endl;
      delete[] values;
   }

   // print out visible and message info
   std::cout << "Visible: " << myObj->getVisible() << "\n";
   const base::String* message = myObj->getMessage();
   std::cout << "Message: " << message->getString() << "\n";

   myObj->unref();

   return 0;
}

} // namespace tutorial
} // namespace oe

//
int main(int argc, char* argv[])
{
   oe::tutorial::main(argc, argv);
}
