#ifndef UTILS
#define UTILS

#include "point.h"
#include "line.h"

#include <vector>

double distance_between_points(point& a, point& b);

bool are_points_within_error(point& a, point& b);

bool is_point_on_line(point& p, line& l);

bool is_point_on_segment(point* p, line& l);

bool is_line_vertical(line& l);

double line_slope(line& l);

bool do_lines_intersect(line& a, line& b);

point intersection_point(line& a, line& b);

std::vector<line> split_line(line& l, point& p);

#endif
