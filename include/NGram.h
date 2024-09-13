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

  void fracture();  
  // Member functions
  long count_polys();

  std::vector<point> get_intersection_points();

  //std::vector<line> get_lines_with_point(point& p);
private:
  // Private variables
  std::vector<line> lines_;

  long trace_path (std::vector<point> history, std::vector<line> lines_remaining);
};

#endif
