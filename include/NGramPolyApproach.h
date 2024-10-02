#ifndef N_GRAM_POLY_APPROACH
#define N_GRAM_POLY_APPROACH

#include "NGram.h"

#include "Connection.h"

#include <vector>

class NGramPolyApproach : public NGram {
 public:
  NGramPolyApproach(int num_vertices);
  NGramPolyApproach(int num_vertices, double radius);
  NGramPolyApproach(std::vector<Connection> c);
  void generate (int num_vertices, double radius) override;
  long count_polys() override;
  std::string to_string() override;
 private:
  std::vector<Connection> connections;

  long compounds_with_poly(unsigned int poly,
			   std::vector<Connection> available_connections);
};
#endif
