/*
 * This struct represents a connection between two "points" which are just uids
 */

#ifndef CONNECTION
#define CONNECTION

struct Connection {
  Connection();
  Connection(a_val,b_val);
  
  unsigned int a;
  unsigned int b;

  bool has_node(unsigned int node);
  bool shares_node(Connection other);
};

#endif
