#ifndef UTILS
#define UTILS

#include "point.h"
#include "line.h"

bool are_points_within_error(point& a, point& b);

bool is_point_on_line(point& p, line& l);

float line_slope(line& a);

bool do_lines_intersect(line& a, line& b);

point intersection_point(line& a, line& b);

#endif
