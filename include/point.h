#ifndef POINT
#define POINT

#include <iostream>

struct point {
  double x;
  double y;

  friend std::ostream& operator << (std::ostream& os, const point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

#endif
