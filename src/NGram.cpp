#include "NGram.h"

#include <cmath>
#include <map>
#include <algorithm>

#include "utils.h"
#include "math_constants.h"
#include "point.h"

// Constructors
NGram::NGram(int num_points) {
  generate(num_points, 100.0);
}

NGram::NGram(int num_points, double radius) {
  generate(num_points, radius);
}

// Destructor
//NGram::~NGram();

// Member functions

// Private functions
void NGram::generate(int num_points, double radius) {
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
  
  for (size_t v=0; v<vertices.size(); v++) {
    for (size_t i=v+1; i<vertices.size(); i++) {
      line l;
      l.a = vertices.at(v);
      l.b = vertices.at(i);
      lines_.push_back(l);
    }
  }
}

// not as efficient as the other method, but I gave up on that one
void NGram::fracture() {
  // create a list of all the points of intersection
  std::vector<point> poi = get_intersection_points();
  
  // iterate through every intersection
  for (auto it_p=poi.begin(); it_p!=poi.end(); ++it_p) {
    // iterate through every line segment
    // note that this needs to be forward iteration, otherwise added segments would be ignored
    for (size_t idx_l=0; idx_l<lines_.size(); ++idx_l) {
      if (is_point_on_segment(*it_p, lines_.at(idx_l))) {
	int fr = is_point_on_segment(*it_p, lines_.at(idx_l));
	std::vector<line> temp = split_line(lines_.at(idx_l), *it_p);
	lines_.erase(lines_.begin() + idx_l);
	lines_.insert(lines_.end(), temp.begin(), temp.end());
	idx_l--;
      }
    }
  }
}

std::vector<point> NGram::get_intersection_points() {
  std::vector<point> poi;
  // find all intersections
  for (auto it1=lines_.begin(); it1!=lines_.end(); ++it1) {
    line i_line = *it1;
    for (auto it2=std::next(it1); it2!=lines_.end(); ++it2) {
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
long NGram::count_polys() {
  long num_polygons = 0;

  std::vector<line> lines_remaining = lines_;

  std::vector<point> points_remaining;
  for (auto it=lines_remaining.begin(); it!=lines_remaining.end(); ++it) {
    point a = it->a;
    point b = it->b;

    if(std::find(points_remaining.begin(), points_remaining.end(), a)==points_remaining.end()) {
      points_remaining.push_back(a);
    }
    if(std::find(points_remaining.begin(), points_remaining.end(), b)==points_remaining.end()) {
      points_remaining.push_back(b);
    }
  }
  //std::cout << "points_remaining.size(): " << points_remaining.size() << std::endl;
  double num_points = points_remaining.size();
  double points_completed = 0;
  for (auto p_it=points_remaining.begin(); p_it!=points_remaining.end(); ++p_it) {
    std::cout << "\r" << ((points_completed+1)*100/num_points) << "% of points with "
	      << num_polygons/2 << " polys found\t\t\t" << std::flush;
    //std::cout << "\n\ninitiating counting procedure on point: " << *p_it << std::endl;
    //std::cout << "remaining lines: " << lines_remaining.size() << std::endl;
    point p = *p_it;

    std::vector<point> h;
    h.push_back(p);
      
    // this is written this way for debugging purposes
    int poly_count = trace_path(h, lines_remaining);
    num_polygons += poly_count;
    //std::cout << "trace finished" << std::endl;
    
    // remove lines that contained the specified starting_point
    for (auto it=lines_remaining.begin(); it!=lines_remaining.end();) {
      if (are_points_within_error(it->a, *p_it)
	  || are_points_within_error(it->b, *p_it)) {
	//std::cout << "deleting line" << std::endl;
	it = lines_remaining.erase(it);
      }
      else {
	++it;
      }
    }
    points_completed++;
  }
  std::cout << std::endl;
  return num_polygons / 2;
}

// the recursive part of the tracing algorithm
long NGram::trace_path (std::vector<point> history, std::vector<line> lines_remaining) {
  //std::cout << "\ttrace depth: " << history.size() << std::endl;
  long num_polygons = 0;
  
  point target_point = history.at(0);
  point current_point = history.at(history.size()-1);
  
  // the possible lines that could be travelled to from current_point
  std::vector<line> options = get_lines_with_point(lines_remaining, current_point);
  if (!are_points_within_error(target_point, current_point)) {
    // remove lines that contained the specified current_point
    for (auto it=lines_remaining.rbegin(); it!=lines_remaining.rend();) {
      //if (is_point_on_line(current_point, *it)) {
      if (are_points_within_error(it->a, current_point)
	  || are_points_within_error(it->b, current_point)) {
	it = std::vector<line>::reverse_iterator(lines_remaining.erase(std::next(it).base()));
	//lines_remaining.erase(it);
      }
      else {
	++it;
      }
    }
  }
  //std::cout << "\t\toptions size: " << options.size() << std::endl;
  // iterate through lines with current_point, starting the recursive method for each one
  for (auto it=options.begin(); it!=options.end(); ++it) { 
    //std::cout << "option: " << *it << std::endl;
    // if the other point completes the polygon, increase polygon counter
    if (it->other(current_point)==target_point) {
      if (history.size() > 2) num_polygons++;
    }
    // otherwise, continue tracing
    else {
      std::vector<point> new_history = history;
      // add the point other than the current point to the history of the new point
      new_history.push_back(it->other(current_point));
      
      num_polygons += trace_path(new_history, lines_remaining);
    }
  }
  return num_polygons;
}

std::string NGram::to_string() {
  std::string str = "Lines: \n";
  
  for (auto l : NGram::lines_) {
    str += "\n" + l.to_string();
  }

  str += std::string("\n\nNGram with " + std::to_string(lines_.size()) + " line segments");

  return str;
}
