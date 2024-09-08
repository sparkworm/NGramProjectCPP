#ifndef POINT
#define POINT

#include <iostream>
#include <string>

struct point {
  double x;
  double y;

point() : x(0.0), y(0.0) {}
  
point(double x_pos, double y_pos) : x(x_pos), y(y_pos) {}
  
  std::string to_string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
  
  friend std::ostream& operator << (std::ostream& os, const point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

#endif
