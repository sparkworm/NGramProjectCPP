// Controls the basic terminal interface.

#ifndef UI
#define UI

#include <iostream>
#include <string>

// The main io loop.  Should return an exit code.
int io_loop();

int line_approach_loop();

int poly_approach_loop();

int matrix_approach_loop();

void start_timer();

void end_timer();

double time_elapsed();

// Function to ask the user for a specific input
template <typename T>
T query_input(const std::string& prompt);

#endif
