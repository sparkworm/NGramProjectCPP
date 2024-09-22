/*
 * This struct represents a connection between two "points" which are just uids
 */

#ifndef CONNECTION
#define CONNECTION

struct Connection {
  Connection();
  Connection(unsigned int a_val, unsigned int b_val);
  
  unsigned int a;
  unsigned int b;

  bool has_node(unsigned int node);
  bool shares_node(Connection other);

  
};

#endif
