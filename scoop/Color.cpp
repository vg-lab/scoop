#include "Color.h"

  std::ostream& operator<< ( std::ostream& os, const scoop::Color& color )
  {
    os << "Color("
       << color.red( ) << ","
       << color.green( ) << ","
       << color.blue( ) << ","
       << color.alpha( ) << ")";
    return os;
  }
