#include "utils.h"

#include <cmath>
#include <algorithm>

// for debugging purposes only
#include <iostream>

double error_limit = 0.001;

double distance_between_points(const point& a, const point& b) {
  return std::sqrt(std::pow((a.x - b.x), 2.0) + std::pow((a.y - b.y), 2.0));
}

bool are_points_within_error(const point& a, const point& b) {
  return std::abs(distance_between_points(a, b)) < error_limit;
}

/* This function returns whether a point falls on a specific line
 * NOTE: this DOES NOT check if the point falls on the specified SEGMENT
 */
bool is_point_on_line(const point& p, const line& l) {
  if (is_line_vertical(l)) {
    return std::abs(l.a.x - p.x) < error_limit;
  }
  return std::abs((l.a.y - p.y) - line_slope(l) * (l.a.x - p.x)) < error_limit;
}

/* This function returns whether a point falls within a specific line segment.
 * NOTE: This function DOES check whether the point fits between the segment endpoints.
 * This function specifically returns false if the point is on one of then endpoints.
 */
bool is_point_on_segment(const point& p, const line& l) {
  // first check if point is on line
  if (!is_point_on_line(p, l)) return false;
  // specifically return false if the point is on one of the endpoints
  if (are_points_within_error(p, l.a) || are_points_within_error(p, l.b)) return false;
  // if the line is vertical, check that it's within y values
  if (is_line_vertical(l)) {
    return std::min(l.a.y, l.b.y) < p.y
      && p.y < std::max(l.a.y, l.b.y);
  }
  return std::min(l.a.x, l.b.x) < p.x
    && p.x < std::max(l.a.x, l.b.x);
}  

/* This function returns whether a point falls within a specific line segment.
 * NOTE: This function DOES check whether the point fits between the segment endpoints.
 * This function specifically returns true if the point is on one of then endpoints.
 */
bool is_point_on_segment_inclusive(const point& p, const line& l) {
  // first check if point is on line
  if (!is_point_on_line(p, l)) return false;
  // if the line is vertical, check that it's within y values
  if (is_line_vertical(l)) {
    return std::min(l.a.y, l.b.y) <= p.y
      && p.y <= std::max(l.a.y, l.b.y)
      || are_points_within_error(p, l.a)
      || are_points_within_error(p, l.b);
  }
  
  return std::min(l.a.x, l.b.x) <= p.x
    && p.x <= std::max(l.a.x, l.b.x)
    || are_points_within_error(p, l.a)
    || are_points_within_error(p, l.b);
}

bool is_line_vertical(const line& l) {
  return std::abs(l.a.x - l.b.x) < error_limit;
}

/* Returns whether a point is above a line.  If the line is vertical, this will return whether the
 * point was to the left of the line.
 * Note that this will return false if the point is on the line
 */
bool is_point_above_line(const point& p, const line& l) {
  if (is_line_vertical(l)) {
    return std::abs(l.a.x - p.x) > error_limit && l.a.x > p.x;
  }
  return (l.a.y - p.y) < line_slope(l) * (l.a.x - p.x);
}

bool are_segments_same_line(const line& l1, const line& l2) {
  if (is_line_vertical(l1) || is_line_vertical(l2)) {
    if (is_line_vertical(l1) && is_line_vertical(l2)) {
      return std::abs(l1.a.x - l2.b.x) < error_limit;
    }
    return false;
  }
  if (std::abs(line_slope(l1) - line_slope(l2)) < error_limit
	&& std::abs(line_value_at(l1, 0.0) - line_value_at(l2, 0.0)) < error_limit) {
  }
  return std::abs(line_slope(l1) - line_slope(l2)) < error_limit
    && std::abs(line_value_at(l1, 0.0) - line_value_at(l2, 0.0)) < error_limit;
}

double line_slope(const line& l) {
  return (l.a.y - l.b.y) / (l.a.x - l.b.x);
}

/* Returns the y value of the line at a given x, or the x at a given y (if vertical) */
double line_value_at(const line& l, const double& v) {
  if (is_line_vertical(l)) {
    return l.a.x;
  }
  return line_slope(l) * (v - l.a.x) + l.a.y;
}

/* Simply returns whether two lines intersect anywhere
 * The only time that it will return false is if the lines are parallel
 */
bool do_lines_intersect(const line& l1, const line& l2) {
  if (is_line_vertical(l1) || is_line_vertical(l2)) {
    return !(is_line_vertical(l1) && is_line_vertical(l2));
  }
  
  return std::abs(line_slope(l1) - line_slope(l2)) > error_limit;
}

/* Function that determines whether two line segments intersect.
 * DOES take into account whether the intersection occurs ON SEGMENTS.
 * Returns false if the intersection is on an endpoint
 */
bool do_segments_intersect(const line& l1, const line& l2) {
  if (!do_lines_intersect(l1, l2)) return false;

  // find the point at which the lines interesect
  point p = intersection_point(l1, l2);

  return is_point_on_segment(p, l1) && is_point_on_segment(p, l2);
}

/* Function that determines whether two line segments intersect.
 * DOES take into account whether the intersection occurs ON SEGMENTS.
 * Returns true if the intersection is on an endpoint
 */
bool do_segments_intersect_inclusive(const line& l1, const line& l2) {
  if (!do_lines_intersect(l1, l2)) return false;

  // find the point at which the lines interesect
  point p = intersection_point(l1, l2);
  
  return is_point_on_segment_inclusive(p, l1) && is_point_on_segment_inclusive(p, l2);
}

/* Assumes that the lines DO intersect.  
 * Also assumes that l1 and l2 are NOT BOTH vertical.  
 * Does NOT bother to check if the intersection point is within a segment.  
 */
point intersection_point(const line& l1, const line& l2) {

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
  
  point p;
  p.x = (m_a * l1.a.x - m_b * l2.a.x - l1.a.y + l2.a.y) / (m_a - m_b);
  p.y = (m_b * l1.a.y - m_a * l2.a.y + (m_a * m_b) * (l2.a.x - l1.a.x)) / (m_b - m_a);
  
  return p;
}

point midpoint(const line& l) {
  if (is_line_vertical(l)) return point(l.a.x,(l.a.y + l.b.y) / 2.0);
  double x = (l.a.x + l.b.x) / 2.0;
  return point(x, line_value_at(l,x));
}

/* This function turns one line into two lines, with the specified point being a shared point
 * between them
 * It is IMPERATIVE that the point it KNOWN to be on the line
 */
std::vector<line> split_line(const line& l, const point& p) {
  std::vector<line> new_lines;
  // can potentially add a resize to minimally improve performance
  
  line l1(l.a, p); // make sure that assigning the reference to p is not a problem here
  line l2(l.b, p);

  new_lines.push_back(l1);
  new_lines.push_back(l2);

  return new_lines;
}
  
std::vector<line> get_lines_with_point(const std::vector<line>& lines, const point& p) {
  std::vector<line> lines_with_point;
  for (auto it=lines.begin(); it!=lines.end(); ++it) {
    if (are_points_within_error(it->a, p) || are_points_within_error(it->b, p)) {
      lines_with_point.push_back(*it);
    }
  }
  return lines_with_point;
}
