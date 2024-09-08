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
    return std::min(l.a.y, l.b.y) < p.y && p.y < std::max(l.a.y, l.b.y);
  }
  return std::abs((l.a.y - p.y) - line_slope(l) * (l.a.x - p.x)) < error_limit;
}

/* This function returns whether a point falls within a specific line segment
 * NOTE: This function DOES check whether the point fits between the segment endpoints
 */
bool is_point_on_segment(point& p, line& l) {
  
}  

bool is_line_vertical(line& l) {
  return std::abs(l.a.x - l.b.x) < error_limit;
}

double line_slope(line& l) {
  return (l.a.y - l.b.y) / (l.a.x - l.b.x);
}

bool do_lines_intersect(line& a, line& b) {
  return std::abs(line_slope(a) - line_slope(b)) < error_limit;
}

point intersection_point(line& a, line& b) {
  double m_a = line_slope(a);
  double m_b = line_slope(b);

  point p;
  p.x = (m_a * a.a.x - m_b * b.a.x - a.a.y + b.a.y) / (m_a - m_b);
  p.y = (m_b * a.a.y - m_a * b.a.y + (m_a * m_b) * (b.a.x - a.a.x)) / (m_b - m_a);

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
  
