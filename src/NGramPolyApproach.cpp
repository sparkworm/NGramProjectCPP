#include "NGramPolyApproach.h"

#include "Polygon.h"
#include "Connection.h"
#include "line.h"


#include <vector>

/* I expect this function to include all of the rings of hell */
void NGramPolyApproach::generate(int num_points, double radius) {
  std::vector<point> vertices;
  vertices.reserve(num_points);

  // Generate the main vertices
  for (int i=0; i<num_points; i++) {
    double angle = math_constants::pi * 2 / num_points * i;
    
    point p;
    p.x = std::cos(angle) * radius;
    p.y = std::sin(angle) * radius;
    
    vertices.push_back(p);
  }

  std::vector<Polygon> polys;
  // create a polygon from the vertices
  Polygon poly(vertices);
  // add main poly to the vector
  polys.push_back(poly);

  // slice polys
  for (size_t v=0; v<vertices.size(); v++) {
    for (size_t i=v+1; i<vertices.size(); i++) {
      line l;
      l.a = vertices.at(v);
      l.b = vertices.at(i);
      // iterate through polys, slicing those that contain the line
      // since polys should all be convex, none should have to be sliced twice
      for (poly p : polys) {
	if (p.does_line_intersect(l)) {
	  polys.push_back(p.slice_poly_off(l));
	}
      }
    }
  }

  // create vector of uids
  /*
  std::vector<unsigned int> uids;
  uids.reserve(polys.size());
  for (unsigned int i=0; i<polys.size(); i++) {
    uids.push_back(i);
  }
  */
  
  // now that all polys are created, we can populate connections
  for (size_t i=0; i<polys.size(); i++) {
    //unsigned int i_uid = uids.at(i);
    for (size_t j=i+1; j<polys.size() j++) {
      //unsigned int j_uid = uids.at(j);
      if (polys.at(i).does_polygon_share_border(polys.at(j))) {
	Connection con(i, j);
	connections.push_back(con);
      }
    }
  }
}

long NGramPolyApproach::count_polys();

std::string to_string();
