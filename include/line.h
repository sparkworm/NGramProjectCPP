#ifndef LINE
#define LINE

#include "point.h"

#include <iostream>

struct line {
  point a;
  point b;

  friend std::ostream& operator << (std::ostream& os, const line& l) {
    os << "[" << l.a << "; " << l.b << "]";
    return os;
  }
    
};

#endif
