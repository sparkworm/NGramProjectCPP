#ifndef N_GRAM
#define N_GRAM

#include <vector>
#include <string>

class NGram {
public:
  // Constructors
  //NGram(int num_points);
  //NGram(int num_points, double radius);
  
  // Destructor
  //~NGram();
  virtual std::string to_string() = 0;
  virtual void generate(int num_points, double radius) = 0;
  // Member functions
  virtual long count_polys() = 0;
private:
};

#endif
