#ifndef N_GRAM_LINE_APPROACH
#define N_GRAM_LINE_APPROACH

#include "NGram.h"

#include "point.h"
#include "line.h"

#include <vector>

class NGramLineApproach : public NGram {
 public:
  void fracture();
  std::vector<point> get_intersection_points();
  //std::vector<line> get_lines_with_point(point& p);
 private:
  std::vector<line> lines_;
  long trace_path (std::vector<point> history, std::vector<line> lines_remaining);

};
#endif
