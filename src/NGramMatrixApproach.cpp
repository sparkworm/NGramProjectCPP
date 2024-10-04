#include "NGramMatrixApproach.h"

#include <cmath>
#include <map>
#include <algorithm>

#include "utils.h"
#include "math_constants.h"
#include "point.h"

long live_poly_count;

NGramMatrixApproach::NGramMatrixApproach(int num_vertices) {
  generate(num_vertices, 100.0);
}
NGramMatrixApproach::NGramMatrixApproach(int num_vertices, double radius) {
  generate(num_vertices, radius);
}

// Private functions
void NGramMatrixApproach::generate(int num_points, double radius) {
  std::vector<point> vertices;
  vertices.reserve(num_points);


  std::vector<line> lines;
  
  // Generate the main vertices
  for (int i=0; i<num_points; i++) {
    double angle = math_constants::pi * 2 / num_points * i;
    
    point p;
    p.x = std::cos(angle) * radius;
    p.y = std::sin(angle) * radius;
    
    vertices.push_back(p);
  }
  
  for (size_t v=0; v<vertices.size(); v++) {
    for (size_t i=v+1; i<vertices.size(); i++) {
      line l;
      l.a = vertices.at(v);
      l.b = vertices.at(i);
      lines.push_back(l);
    }
  }

  /* Fracturing procedure */
  // create a list of all the points of intersection
  std::vector<point> poi = get_intersection_points(lines);
  
  // iterate through every intersection
  for (auto it_p=poi.begin(); it_p!=poi.end(); ++it_p) {
    // iterate through every line segment
    // note that this needs to be forward iteration, otherwise added segments would be ignored
    for (size_t idx_l=0; idx_l<lines.size(); ++idx_l) {
      if (is_point_on_segment(*it_p, lines.at(idx_l))) {
	int fr = is_point_on_segment(*it_p, lines.at(idx_l));
	std::vector<line> temp = split_line(lines.at(idx_l), *it_p);
	lines.erase(lines.begin() + idx_l);
	lines .insert(lines.end(), temp.begin(), temp.end());
	idx_l--;
      }
    }
  }
  
  std::cout << "number of segments: " << lines.size() << std::endl;
  
  // create a list of all the points of intersection
  std::vector<point> points;
  for (auto l : lines) {
    if (std::find(points.begin(), points.end(), l.a)==points.end()) points.push_back(l.a);
    if (std::find(points.begin(), points.end(), l.b)==points.end()) points.push_back(l.b);
  }

  std::cout << "number of points: " << points.size() << std::endl;

  //std::vector<std::vector<int>> adj_mat;

  // create adj_mat.  the index of each point of intersection should be the number of that point
  for (size_t i=0; i<points.size(); i++) {
    std::vector<int> adj_vec;
    for (size_t j=0; j<points.size(); j++) {
      // hypothetical line
      line hpth_l(points.at(i), points.at(j));
      adj_vec.push_back(std::find(lines.begin(), lines.end(), hpth_l)==lines.end() ? 0 : 1);
    }
    adj_mat.push_back(adj_vec);
  }
}

std::vector<point> NGramMatrixApproach::get_intersection_points(std::vector<line> lines) {
  std::vector<point> poi;
  // find all intersections
  for (auto it1=lines.begin(); it1!=lines.end(); ++it1) {
    line i_line = *it1;
    for (auto it2=std::next(it1); it2!=lines.end(); ++it2) {
      line j_line = *it2;
      if (do_segments_intersect(i_line, j_line)) {
	point intersection = intersection_point(i_line, j_line);
	// check if this intersection is new to the list
	if (std::find(poi.begin(), poi.end(), intersection) == poi.end()) {
	  poi.push_back(intersection);
	}
      }
    }
  }
  return poi;
}

// this is the big boy, the one that does the important work
/* 
 * Should lead into a recursive function that branches into the various paths
 */
long NGramMatrixApproach::count_polys() {
  long num_polygons = 0;

  std::vector<std::vector<int>> adj_mat_backup = adj_mat;

  int p = 0;
  std::cout << std::endl;
  while (adj_mat.size() > 0) {
    const int const_p = p;
    std::vector<int> history;
    history.resize(adj_mat.size());
    num_polygons+=trace_path(p, const_p, history, 0);
    /* remove p from adj_mat */
    adj_mat.erase(adj_mat.begin());
    for (auto& vec : adj_mat) {
      vec.erase(vec.begin());
    }
  }

  std::cout << std::endl;
  
  adj_mat = adj_mat_backup;
  
  return num_polygons / 2;
}

// the recursive part of the tracing algorithm
long NGramMatrixApproach::trace_path (int point, const int& target, std::vector<int> history,
				      int depth) {
  long num_polygons = 0;
  depth++;
  
  history.at(point) = 1;
  
  // iterates through the adjacency vector of the given point
  for (size_t i=0; i<adj_mat.at(point).size(); i++) {
    /* checks that the point is adjacent according to the adj_mat and that it has not been
       visited before */
    if (adj_mat.at(point).at(i)) {
      /* if the point is the target, and the search has gone on for more than 2 iterations,
	 increase the poly count, since this means a poly has been traced */
      if (i==target && depth > 2) {
	num_polygons++;
	live_poly_count++;
	std::cout << "\r" << live_poly_count/2;
      }
      /* checks if the point i has been visited */
      else if (!history.at(i)) {
	num_polygons += trace_path(i, target, history, depth);
      }
    }
  }
  
  return num_polygons;
}

std::string NGramMatrixApproach::to_string() {
  std::string str;
  str += std::string("\n\nNGram with adjacency matrix: \n");

  for (auto vec : adj_mat) {
    for (auto scalar : vec) {
      std::cout << scalar << " ";
    }
    std::cout << std::endl;
  }
  return str;
}
