#include "Polygon.h"

#include "utils.h"

#include <algorithm>

// for debugging purposes
#include <iostream>

/* do note that point must be in the correct order for this to work */
Polygon::Polygon(std::vector<point> points) {
  // add wrapping-around line
  lines_.push_back(line(points.at(points.size()-1), points.at(0))); 
  // Create a line between each pair of points except for the very last one
  for (size_t i=0; i<points.size()-1; i++) {
    lines_.push_back(line(points.at(i), points.at(i+1)));
  }
}

Polygon::Polygon(std::vector<line> lines) {
  lines_ = lines;
}

bool Polygon::does_polygon_share_border(Polygon other) {
  for (line l1 : other.lines_) {
    for (line l2 : lines_) {
      if (l1==l2) return true;
    }
  }
  return false;
}

bool Polygon::does_line_intersect(line l) {
  for (line l2: lines_) {
    if (do_segments_intersect_inclusive(l, l2)) return true;
  }
  return false;
}

bool Polygon::can_slice_poly_off(line l) {
  //return does_line_intersect(l);
  std::cout << points_of_intersection(l).size() << std::endl;
  return (points_of_intersection(l).size() == 2);
}

/* This function returns one of the pieces created when intersected by a line.  
 * The original polygon becomes the other piece.
 * This function should only be called if can_slice_poly_off() is true
 */
Polygon Polygon::slice_poly_off(line l) {
  std::vector<line> lines_above;
  std::vector<line> lines_below;
  
  /* iterate through lines_, placing each segment into either lines_above or lines_below */
  for (line seg : lines_) {
    /* if the segments intersect non-inclusively, that means that one point is above and one 
       point is below.  This is important for later */
    if (do_segments_intersect(seg, l)) {
      std::cout << "a" << std::endl;
      point poi = intersection_point(seg, l);
      line seg1(seg.a, poi), seg2(seg.a, poi);
      /* Check if seg1 is above the line */
      if (is_point_above_line(seg.a, l)) {
	lines_above.push_back(seg1);
	lines_below.push_back(seg2);
      }
      else if (is_point_above_line(seg.b, l)) {
	lines_above.push_back(seg2);
	lines_below.push_back(seg1);
      }	
    }
    /* Since intersection has already been checked for, if one point is above, 
       so is the other */
    else if (is_point_above_line(seg.a, l) || is_point_above_line(seg.b, l)) {
      std::cout << "b" << std::endl;
      lines_above.push_back(seg);
    }
    // redundant
    else if (!is_point_above_line(seg.a, l) || !is_point_above_line(seg.b, l)) {
      std::cout << "c" << std::endl;
      lines_below.push_back(seg);
    }
    else {
      std::cout << "This is bad I think" << std::endl;
      // bad
    }
  }

  /* There should now be two points on both lines_above and lines_below that aren't 
     connected by a line */
  std::cout << "test" << std::endl;
  std::vector<point> pois = points_of_intersection(l);
  std::cout << "test2" << std::endl;
  line cropped_l(pois.at(0), pois.at(1));
  lines_above.push_back(cropped_l);
  lines_below.push_back(cropped_l);
  
  lines_ = lines_above;
  std::cout << "lines_ length: " << lines_.size() << std::endl;
  Polygon new_poly(lines_below);
  return new_poly;
}

std::vector<point> Polygon::points_of_intersection(line l) {
  std::vector<point> poi;
  for (line l2: lines_) {
    if(do_segments_intersect_inclusive(l, l2)
       && std::find(poi.begin(), poi.end(), intersection_point(l, l2))==poi.end()) {
      poi.push_back(intersection_point(l, l2));
    }
    else if (are_segments_same_line(l, l2)) {
      std::cout << "two are the same: " << l << ", " << l2 << std::endl;
      poi.clear();
      return poi;
    }
  }
  return poi;
}

std::string Polygon::to_string() {
  std::string str = "";

  str += std::string("Polygon with " + std::to_string(lines_.size()) + " lines\n");

  for (line l : lines_) {
    str += std::string("\t" + l.to_string() + "\n");
  }

  return str;
}
