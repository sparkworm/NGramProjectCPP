#include "NGram.h"

#include <cmath>
#include <map>
#include <algorithm>

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

// not as efficient as the other method, but I gave up on that one
void NGram::fracture() {
  // create a list of all the points of intersection
  std::vector<point> poi;

  // find all intersections
  for (auto it1=lines_.begin(); it1!=lines_.end(); ++it1) {
    line i_line = *it1;
    for (auto it2=std::next(it1); it2!=lines_.end(); ++it2) {
      line j_line = *it2;
      if (do_segments_intersect(i_line, j_line)) {
	point intersection = intersection_point(i_line, j_line);
	// check if this intersection is new to the list
	if (std::find(poi.begin(), poi.end(), intersection) == poi.end()) {
	  poi.push_back(intersection);
	}
      }
    }
  }
  // iterate through every intersection
  for (auto it_p=poi.begin(); it_p!=poi.end(); ++it_p) {
    // iterate through every line segment
    // note that this needs to be forward iteration, otherwise added segments would be ignored
    for (size_t idx_l=0; idx_l<lines_.size(); ++idx_l) {
      if (is_point_on_segment(*it_p, lines_.at(idx_l))) {
	int fr = is_point_on_segment(*it_p, lines_.at(idx_l));
	std::vector<line> temp = split_line(lines_.at(idx_l), *it_p);
	lines_.erase(lines_.begin() + idx_l);
	lines_.insert(lines_.end(), temp.begin(), temp.end());
	idx_l--;
      }
    }
  }
}

/*
void NGram::fracture() {
  //std::vector<line> new_lines = lines_;
  
  for (size_t i=0; i<lines_.size(); i++) {
    line main_l = lines_.at(i);
    //  create a map to track all intersections with the given line
    // key: line index
    // value: point of intersection
    std::map<size_t, point> intersections;
    // iterates backwards
    for (size_t j=lines_.size()-1; j>i; j--) {
      if (do_segments_intersect(main_l, lines_.at(j))) {
	std::cout << "intersection found" << std::endl;
	// sets the value of idx to the point of intersection
	intersections[j] = intersection_point(main_l, lines_.at(j));
      }
    }
    // if there are intersecting lines
    if (intersections.size() > 0) {
      std::cout << "Intersections present!" << std::endl;
      std::vector<line> temp;
      temp.reserve(2);
      
      //temp = split_line(main_l, i_p);
      //lines_.insert(lines_.end(), temp.begin(), temp.end());

      std::vector<line> main_l_fragments;
      main_l_fragments.push_back(main_l);
      
      for (auto& [key, value] : intersections) {
	temp = split_line(lines_.at(key), value);
	for (auto& bob : temp) {
	  std::cout << bob << std::endl;
	}
	lines_.insert(lines_.end(), temp.begin(), temp.end());

	for (auto it=main_l_fragments.rbegin(); it != main_l_fragments.rend(); ++it) {
	  std::cout << "main_l_fragment: " << *it << std::endl;
	  if (is_point_on_line(value, *it)) {
	    std::cout << "\tIntersection found!" << std::endl;
	    temp = split_line(*it,
	    for (auto& bob : temp) {
	      std::cout << "\t" << bob << std::endl;
	      }
	    // create a normal iterator from it so that erase() can be called
	    auto forward_it = std::next(it).base();
	    // erase the segment that was split
	    main_l_fragments.erase(forward_it);
	    // add the segments that resulted from the split
	    main_l_fragments.insert(main_l_fragments.end(), temp.begin(), temp.end());
	    break;
	  }
	}
	//lines_.erase(lines_.begin() + key);
      }
      
      
      lines_.insert(lines_.end(), main_l_fragments.begin(), main_l_fragments.end());
      
      
      for (auto it = intersections.rbegin(); it != intersections.rend(); ++it) {
	//auto forward_it = std::next(it).base();
	lines_.erase(lines_.begin() + it->first);
      }
      
      //      lines_.erase(lines_.begin() + j);
      lines_.erase(lines_.begin() + i);
      
      //lines_.insert(lines_.end(), fragments.begin(), fragments.end());

      i--;
    }	
  }
}
*/

std::string NGram::to_string() {
  std::string str = "Lines: \n";
  
  for (auto l : NGram::lines_) {
    str += "\n" + l.to_string();
  }

  str += std::string("\n\nNGram with " + std::to_string(lines_.size()) + " line segments");

  return str;
}
