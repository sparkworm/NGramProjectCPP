#ifndef LINE
#define LINE

#include "point.h"

#include <iostream>
#include <string>

struct line {
  point a;
  point b;

line() : a(point()), b(point()) {}
  
line(point point1, point point2) : a(point1), b(point2) {}
  
  std::string to_string() const {
    return "[" + a.to_string() + "; " + b.to_string() + "]";
  }
  
  friend std::ostream& operator << (std::ostream& os, const line& l) {
    os << "[" << l.a << "; " << l.b << "]";
    return os;
  }
    
};

#endif
