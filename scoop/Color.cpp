#include "Color.h"

namespace scoop
{

  std::ostream& operator<< ( std::ostream& os, const QColor color )
  {
    os << "Color("
       << color.red( ) << ","
       << color.green( ) << ","
       << color.blue( ) << ","
       << color.alpha( ) << ")";
    return os;
  }

} // namespace scoop
