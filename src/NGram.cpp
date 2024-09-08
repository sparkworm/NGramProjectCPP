#include "NGram.h"

#include <cmath>

#include "math_constants.h"
#include "point.h"

// Constructors
NGram::NGram(int num_points) {
  generate(num_points, 100.0);
}

NGram::NGram(int num_points, double radius) {
  generate(num_points, radius);
}

// Destructor
//NGram::~NGram();

// Member functions

// Private functions
void NGram::generate(int num_points, double radius) {
  std::vector<point> vertices;
  vertices.reserve(num_points);

  // Generate the main vertices
  for (int i=0; i<num_points; i++) {
    double angle = math_constants::pi * 2 / num_points * i;
    
    point p;
    p.x = std::cos(angle) * radius;
    p.y = std::sin(angle) * radius;
    
    vertices.push_back(p);
  }
  
  for (size_t v=0; v<vertices.size(); v++) {
    for (size_t i=v+1; i<vertices.size(); i++) {
      line l;
      l.a = vertices.at(v);
      l.b = vertices.at(i);
      lines_.push_back(l);
    }
  }
}

std::string NGram::to_string() {
  std::string str = "Lines: \n";
  
  for (auto l : NGram::lines_) {
    str += "\n" + l.to_string();
  }

  return str;
}
