/* 
 * This should be a class for the polygons used in the polygon approach to the problem.
 * Ideally, the polygons should be easily converted to Nodes, which will be used in the 
 * actual solution.
 */
#ifndef POLYGON
#define POLYGON

#include "line.h"

#include <vector>

class Polygon {
 public:
  Polygon(std::vector<point> points);
  
  bool does_polygon_share_border(Polygon other);
 private:
  std::vector<line> lines_;
};

#endif
