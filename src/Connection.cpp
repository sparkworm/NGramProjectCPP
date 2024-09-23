#include "Connection.h"

Connection::Connection() : a(0), b(0) {}
Connection::Connection(unsigned int a_val, unsigned int b_val) : a(a_val), b(b_val) {}

bool Connection::has_node(unsigned int node) {
  return (a==node || b==node);
}

bool Connection::shares_node(Connection other) {
  return has_node(other.a) || has_node(other.b);
  //return (other.a==a || other.a==b || other.b==a || other.b==b);
}

/* returns the node that doesn't equal this.
   Will return b if neither equals this */
unsigned int Connection::other_node(unsigned int node) {
  return (node==a) ? b : a;
}
