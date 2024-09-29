#include "NGramPolyApproach.h"

#include <cmath>

#include <algorithm>

#include "math_constants.h"
#include "Polygon.h"
#include "Connection.h"
#include "line.h"

#include <vector>

// here for debugging purposes
#include <iostream>

NGramPolyApproach::NGramPolyApproach(int num_vertices) {
  generate(num_vertices, 100.0);
}

NGramPolyApproach::NGramPolyApproach(int num_vertices, double radius) {
  generate(num_vertices, radius);
}

/* I expect this function to include all of the rings of hell */
void NGramPolyApproach::generate(int num_points, double radius) {
  std::vector<point> vertices;
  //vertices.reserve(num_points);

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
      for (size_t pi=0; pi<polys.size(); pi++) {
	if (polys.at(pi).can_slice_poly_off(l)) {
	  polys.push_back(polys.at(pi).slice_poly_off(l));
	}
      }
    }
  }

  std::cout << "Number of polys after slicing: " << polys.size() << std::endl;
  
  // now that all polys are created, we can populate connections
  for (size_t i=0; i<polys.size(); i++) {
    //unsigned int i_uid = uids.at(i);
    //std::cout << "i: " << i << std::endl;
    for (size_t j=i+1; j<polys.size(); j++) {
      //unsigned int j_uid = uids.at(j);
      //std::cout << "\tj: " << j << std::endl;
      if (polys.at(i).does_polygon_share_border(polys.at(j))) {
	//std::cout << "border shared." << std::endl;
	Connection con(i, j);
	connections.push_back(con);
      }
    }
  }
  std::cout << "Number of connections: " << connections.size() << std::endl;
}

long NGramPolyApproach::count_polys() {
  return compounds_with_poly(connections.at(0).a, connections);
}

long NGramPolyApproach::compounds_with_poly(unsigned int poly,
					    std::vector<Connection> available_connections) {
  long count = 1;
  std::vector<Connection> connected;
  for (Connection c : available_connections) {
    if (c.has_node(poly)) connected.push_back(c);
  }
  // remove self from list of connections
  for (Connection c : connected) {
    count += compounds_with_poly(c.other_node(poly), available_connections);
    // remove other poly from list of connections.
  }
  return count;
}

std::string NGramPolyApproach::to_string() {
  std::string str = "";

  str += "NGramPolyApproach";

  str += std::string("\tConnections: " + std::to_string(connections.size()));
  return str;
}
