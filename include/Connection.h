<<<<<<< HEAD
/*
 * This struct represents a connection between two "points" which are just uids
 */
=======

>>>>>>> 761f1561dd29233cfd588b7c8fc2c72300a51099

#ifndef CONNECTION
#define CONNECTION

struct Connection {
  Connection();
<<<<<<< HEAD
  Connection(a_val,b_val);
=======
  Connection(a,b);
>>>>>>> 761f1561dd29233cfd588b7c8fc2c72300a51099
  
  unsigned int a;
  unsigned int b;

  bool has_node(unsigned int node);
  bool shares_node(Connection other);
};

#endif
