#include "Polygon.h"

#include "utils.h"

/* do note that point must be in the correct order for this to work */
Polygon::Polygon(std::vector<point> points) {
  // add wrapping-around line
  lines_.push_back(line(points.size()-1, points.at(0))); 
  // Create a line between each pair of points except for the very last one
  for (size_t i=0; i<points.size-1; i++) {
    lines_.push_back(line(points.at(i), points.at(i+1)));
  }
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
    if (do_segments_intersect(l, l2)) return true;
  }
  return false;
}

bool Polygon::can_slice_poly_off(line l) {
  return (points_of_intersection(l).size() == 2);
}

/* This function returns one of the pieces created when intersected by a line.  The original polygon
 * becomes the other piece.
 * This function should only be called if can_slice_poly_off() is true
 */
Polygon Polygon::slice_poly_off(line l) {
  std::vector<point> points_below;
  std::vector<point> points_above;

  // INCOMPLETE
}
  

std::vector<point> points_of_intersection(line l) {
  std::vector<point> poi;
  for (line l2: lines_) {
    if(do_segments_intersect(l, l2)) {
      poi.push_back(intersection_point(l, l2));
    }
  }
  return poi;
}
