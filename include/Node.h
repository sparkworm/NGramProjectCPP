/*
 * This class should be used to represent the abstract relationship between polygons in the 
 * polygon approach to the problem.  A node should be aware of its neighbors.
 */

#ifndef NODE
#define NODE

#include <vector>

class Node {
 public:
  Node();

  void add_neighbor(Node neighbor);
  void add_neighbors(std::vector<Node> neighbors);
  void remove_neighbor(Node neighbor);
  void remove_all_neighbors();
  bool is_node_neighbor(Node other);
  std::vector<Node> get_neighbors();

  friend bool operator == (const Node& node1, const Node& node2);
 private:
  std::vector<Node> neighbors_;
  int uid;
};

#endif
