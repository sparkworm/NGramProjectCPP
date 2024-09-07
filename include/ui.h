// Controls the basic terminal interface.

#ifndef UI
#define UI

#include <iostream>
#include <string>

// The main io loop.  Should return an exit code.
int io_loop();

// Function to ask the user for a specific input
template <typename T>
T query_input(std::string prompt);

#endif
