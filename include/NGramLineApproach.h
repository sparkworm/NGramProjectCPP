#ifndef N_GRAM_LINE_APPROACH
#define N_GRAM_LINE_APPROACH

#include "NGram.h"

#include "point.h"
#include "line.h"

#include <vector>

class NGramLineApproach : public NGram {
 public:
  NGramLineApproach(int num_vertices);
  NGramLineApproach(int num_vertices, double radius);
  void generate (int num_vertices, double radius) override;
  long count_polys() override;
  void fracture();
  std::vector<point> get_intersection_points();
  //std::vector<line> get_lines_with_point(point& p);
  std::string to_string();
 private:
  std::vector<line> lines_;
  long trace_path (std::vector<point> history, std::vector<line> lines_remaining);
};
#endif
