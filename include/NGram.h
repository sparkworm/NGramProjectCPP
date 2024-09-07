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
  ~NGram();
  
  // Member functions
  int count_polys();
private:
  // Private variables
  std::vector<line> lines_;

  // Private functions
  void generate(int num_points, double radius);

  std::string to_string();
};

#endif
