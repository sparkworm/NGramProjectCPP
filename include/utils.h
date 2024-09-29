#ifndef UTILS
#define UTILS

#include "point.h"
#include "line.h"

#include <vector>

double distance_between_points(const point& a, const point& b);
bool are_points_within_error(const point& a, const point& b);
bool is_point_on_line(const point& p, const line& l);
bool is_point_on_segment(const point& p, const line& l);
bool is_point_on_segment_inclusive(const point& p, const line& l);
bool is_line_vertical(const line& l);
bool is_point_above_line(const point& p, const line& l);
bool are_segments_same_line(const line& l1, const line& l2);
double line_slope(const line& l);
double line_value_at(const line& l, const double& v);
bool do_lines_intersect(const line& l1, const line& l2);
bool do_segments_intersect(const line& l1, const line& l2);
bool do_segments_intersect_inclusive(const line& l1, const line& l2);
point intersection_point(const line& a, const line& b);
point midpoint(const line& l);
std::vector<line> split_line(const line& l, const point& p);
std::vector<line> get_lines_with_point(const std::vector<line>& lines, const point& p);

#endif
