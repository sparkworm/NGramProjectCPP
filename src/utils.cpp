#include "utils.h"

#include <cmath>
#include <algorithm>

// for debugging purposes only
#include <iostream>

double error_limit = 0.001;

double distance_between_points(point& a, point& b) {
  return std::sqrt(std::pow((a.x - b.x), 2.0) + std::pow((a.y - b.y), 2.0));
}

bool are_points_within_error(point& a, point& b) {
  return std::abs(distance_between_points(a, b)) < error_limit;
}

/* This function returns whether a point falls on a specific line
 * NOTE: this DOES NOT check if the point falls on the specified SEGMENT
 */
bool is_point_on_line(point& p, line& l) {
  if (is_line_vertical(l)) {
    return std::abs(l.a.x - p.x) < error_limit;
  }
  return std::abs((l.a.y - p.y) - line_slope(l) * (l.a.x - p.x)) < error_limit;
}

/* This function returns whether a point falls within a specific line segment
 * NOTE: This function DOES check whether the point fits between the segment endpoints
 */
bool is_point_on_segment(point& p, line& l) {
  // first check if point is on line
  if (!is_point_on_line) return false;
  // if the line is vertical, check that it's within y values
  if (is_line_vertical(l)) {
    return std::min(l.a.y, l.b.y) < p.y && p.y < std::max(l.a.y, l.b.y);
  }
  return std::min(l.a.x, l.b.x) < p.x && p.x < std::max(l.a.x, l.b.x);
}  

bool is_line_vertical(line& l) {
  return std::abs(l.a.x - l.b.x) < error_limit;
}

double line_slope(line& l) {
  return (l.a.y - l.b.y) / (l.a.x - l.b.x);
}

bool do_lines_intersect(line& l1, line& l2) {
  if (is_line_vertical(l1) || is_line_vertical(l2)) {
    return !(is_line_vertical(l1) && is_line_vertical(l2));
  }
  
  return std::abs(line_slope(l1) - line_slope(l2)) < error_limit;
}

/* Assumes that the lines DO intersect.  
 * Also assumes that l1 and l2 are NOT BOTH vertical.  
 * Does NOT bother to check if the intersection point is within a segment.  
 */
point intersection_point(line& l1, line& l2) {

  if (is_line_vertical(l1)) {
    point p;
    p.x = l1.a.x;
    p.y = l2.a.y - (line_slope(l2) * (l2.a.x - p.x));
    return p;
  }

  if (is_line_vertical(l2)) {
    point p;
    p.x = l2.a.x;
    p.y = l1.a.y - (line_slope(l1) * (l1.a.x - p.x));
    return p;
  }
  
  double m_a = line_slope(l1);
  double m_b = line_slope(l2);

  std::cout << m_a - m_b << std::endl;
  
  point p;
  p.x = (m_a * l1.a.x - m_b * l2.a.x - l1.a.y + l2.a.y) / (m_a - m_b);
  p.y = (m_b * l1.a.y - m_a * l2.a.y + (m_a * m_b) * (l2.a.x - l1.a.x)) / (m_b - m_a);
  std::cout << p.x << std::endl;
  
  /*
    var x_a: float = point0.position.x
    var x_b: float = other.point0.position.x
    var y_a: float = point0.position.y
    var y_b: float = other.point0.position.y
	
    var x: float = (m_a * x_a - m_b * x_b - y_a + y_b) / (m_a - m_b)
    var y: float = (m_b * y_a - m_a * y_b + (m_a * m_b) * (x_b - x_a)) / (m_b - m_a)
   */
  
  return p;
}

/* This function turns one line into two lines, with the specified point being a shared point
 * between them
 * It is IMPERATIVE that the point it KNOWN to be on the line
 */
std::vector<line> split_line(line& l, point& p) {
  std::vector<line> new_lines;
  // can potentially add a resize to minimally improve performance
  
  line l1(l.a, p); // make sure that assigning the reference to p is not a problem here
  line l2(l.b, p);

  new_lines.push_back(l1);
  new_lines.push_back(l2);

  return new_lines;
}
  
