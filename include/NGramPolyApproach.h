#ifndef N_GRAM_POLY_APPROACH
#define N_GRAM_POLY_APPROACH

#include "NGram.h"

#include "Connection.h"

#include <vector>

class NGramPolyApproach : public NGram {
 public:
  NGramPolyApproach(int num_vertices);
  NGramPolyApproach(int num_vertices, double radius);
  void generate (int num_vertices, double radius) override;
  long count_polys() override;
 private:
  std::vector<Connection> connections;
};
#endif
