#include "point.h"

#include "utils.h"

bool operator == (const point& lp, const point& rp) {
  return are_points_within_error(lp, rp);
}
