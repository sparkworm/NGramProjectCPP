#include "line.h"

line::line() : a(point()), b(point()) {}

line::line(point point1, point point2) : a(point1), b(point2) {}

std::string line::to_string() const {
  return "polygon(" + a.to_string() + ", " + b.to_string() + ")";
  //return "[" + a.to_string() + "; " + b.to_string() + "]";
}
  
std::ostream& operator << (std::ostream& os, const line& l) {
  os << "polygon(" << l.a << ", " << l.b << ")";
  //os << "[" << l.a << "; " << l.b << "]";
  return os;
}  
