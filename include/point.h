#ifndef POINT
#define POINT

#include <iostream>
#include <string>

struct point {
  double x;
  double y;

  std::string to_string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
  
  friend std::ostream& operator << (std::ostream& os, const point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

#endif
