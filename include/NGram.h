#ifndef N_GRAM
#define N_GRAM

#include <vector>
#include <string>
#include "line.h"

class NGram {
public:
  // Constructors
  NGram(int num_points);
  NGram(int num_points, double radius);
  // Destructor
  //~NGram();
  std::string to_string();
  void generate(int num_points, double radius);
  // Member functions
  long count_polys();
private:
};

#endif
