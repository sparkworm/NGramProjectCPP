#ifndef N_GRAM_MATRIX_APPROACH
#define N_GRAM_MATRIX_APPROACH

#include "NGram.h"

#include "point.h"
#include "line.h"

#include <vector>

class NGramMatrixApproach : public NGram {
 public:
  NGramMatrixApproach(int num_vertices);
  NGramMatrixApproach(int num_vertices, double radius);
  void generate (int num_vertices, double radius) override;
  long count_polys() override;
  std::vector<point> get_intersection_points(std::vector<line> lines);
  //std::vector<line> get_lines_with_point(point& p);
  std::string to_string() override;
 private:
  std::vector<std::vector<int>> adj_mat;
  long trace_path (int point, const int& target, std::vector<int> history);
};
#endif
