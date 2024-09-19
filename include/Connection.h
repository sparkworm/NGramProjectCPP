

#ifndef CONNECTION
#define CONNECTION

struct Connection {
  Connection();
  Connection(a,b);
  
  unsigned int a;
  unsigned int b;

  bool has_node(unsigned int node);
  bool shares_node(Connection other);
};

#endif
