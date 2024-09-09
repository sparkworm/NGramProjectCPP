#include "NGram.h"

#include <cmath>

#include "utils.h"
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

void NGram::fracture() {
  //std::vector<line> new_lines = lines_;
  
  for (size_t i=0; i<lines_.size(); i++) {
    line main_l = lines_.at(i);
    for (size_t j=i+1; j<lines_.size(); j++) {
      line other_l = lines_.at(j);
      // check if the segments intersect
      // if so, both lines should be fragmented, and their fragments appended to the back
      // the original lines should immediately be removed, and the iteration should move on.
      if (do_segments_intersect(main_l, other_l)) {
        point i_p = intersection_point(main_l, other_l);
	//std::vector<line> fragments;
	// there should always be 4 items
	//fragments.reserve(4);

	std::vector<line> temp;
	temp.reserve(2);
	  
	temp = split_line(main_l, i_p);
	lines_.insert(lines_.end(), temp.begin(), temp.end());
	
	temp = split_line(other_l, i_p);
	lines_.insert(lines_.end(), temp.begin(), temp.end());

	lines_.erase(lines_.begin() + i);
	lines_.erase(lines_.begin() + j);

	//lines_.insert(lines_.end(), fragments.begin(), fragments.end());

	i--;
	break;
      }	
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
