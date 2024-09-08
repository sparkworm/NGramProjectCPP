#ifndef LINE
#define LINE

#include "point.h"

#include <iostream>
#include <string>

struct line {
  point a;
  point b;

  std::string to_string() const {
    return "[" + a.to_string() + "; " + b.to_string() + "]";
  }
  
  friend std::ostream& operator << (std::ostream& os, const line& l) {
    os << "[" << l.a << "; " << l.b << "]";
    return os;
  }
    
};

#endif
