#ifndef UTILS
#define UTILS

#include "point.h"
#include "line.h"

#include <vector>

double distance_between_points(point& a, point& b);

bool are_points_within_error(const point& a, const point& b);

bool is_point_on_line(point& p, line& l);

bool is_point_on_segment(point& p, line& l);

bool is_line_vertical(line& l);

double line_slope(line& l);

bool do_lines_intersect(line& l1, line& l2);

bool do_segments_intersect(line& l1, line& l2);

point intersection_point(line& a, line& b);

std::vector<line> split_line(line& l, point& p);

std::vector<line> get_lines_with_point(std::vector<line>& lines, point& p);

#endif
