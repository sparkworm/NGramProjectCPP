// The source code for the UI loop
#include "ui.h"

#include "NGram.h"
#include "NGramLineApproach.h"
#include "NGramPolyApproach.h"
#include "NGramMatrixApproach.h"
#include "Timer.h"
// might remove this later, it's only here for testing purposes at the moment
#include "utils.h"
#include "Polygon.h"
#include <vector>

#include <iostream>
#include <limits>

std::string line_approach_main_menu = std::string("\n\nWhat would you like to do?"
						  "\n\t0: Quit"
						  "\n\t1: Create Shape"
						  "\n\t2: Fracture shape"
						  "\n\t3: Count polygons"
						  "\n\t4: View shape");

std::string poly_approach_main_menu = std::string("\n\nWhat would you like to do?"
						  "\n\t0: Quit"
						  "\n\t1: Create shape"
						  "\n\t2: Count polygons"
						  "\n\t3: View shape");

std::string matrix_approach_main_menu = std::string("What would you like to do?"
						    "\n\t0: Quit"
						    "\n\t1: Create shape"
						    "\n\t2: Count polygons"
						    "\n\t3: View shape");

std::string approach_query = std::string("\n\nWhat approach would you like to use?"
					 "\n\t0: line_approach"
					 "\n\t1: poly_approach (bad)"
					 "\n\t2: matrix_approach (best)");

int io_loop() {
  int option = query_input<int>(approach_query);

  switch(option) {
  case 0:
    return line_approach_loop();
  case 1:
    return poly_approach_loop();
  case 2:
    return matrix_approach_loop();
  default:
    return 1;
  }
}

int matrix_approach_loop() {
  Timer timer;
  // initialize a pointer to what will later be the NGram
  NGramMatrixApproach* n_gram = nullptr;

  while (true) {
    
    int option = query_input<int>(matrix_approach_main_menu);
    
    switch (option) {
    case 0:
      std::cout << "Exiting..." << std::endl;
      return 0;

    case 1: {
      std::cout << "Creating shape..." << std::endl;
      // Ask for the number of main vertices that the NGram should have
      int num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      // Continue asking for the number of vertices until a valid answer is given.
      // The number of vertices must be greater than 3 in order to form an actual NGram.
      while (num_vertices < 3) {
	std::cout << "Number of vertices must be 3 or higher!" << std::endl;
	num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      }
      // Assign the now created NGram to the n_gram pointer.
      n_gram = new NGramMatrixApproach(num_vertices);
      break;
    }

    case 2:
      std::cout << "Counting polygons..." << std::endl;
      if (n_gram == nullptr) {
	std::cout << "NO SHAPE DEFINED" << std::endl;
      }
      else {
	timer.start();
	long num_polys = n_gram->count_polys();
	std::cout << "Number of polygons: " << num_polys << std::endl;
	timer.stop();
	timer.display_time_passed();
      }
      break;

    case 3:
      std::cout << "Printing shape..." << std::endl;
      // Check if there is an NGram assigned to n_gram
      if (n_gram != nullptr) {
	// If there is an object, print NGram
	std::cout << n_gram->to_string() << std::endl;
      }
      else {
	// If the pointer is null, an NGram has not been created.
	std::cout << "Shape has not yet been created!" << std::endl;
      }
      break;

    default:
      std::cout << "Unknown input" << std::endl;
      break;
    }
  }
  delete n_gram;
  return 0;
}

int poly_approach_loop () {
  /* DEBUGGING ZONE */

  std::vector<Connection> connections;
  connections.push_back(Connection(0,1));
  connections.push_back(Connection(1,2));
  connections.push_back(Connection(2,0));
  
  NGramPolyApproach test_n_gram(connections);

  std::cout << "Test NGram poly count: " << test_n_gram.count_polys() << std::endl;
  
  /* END OF DEBUGGING ZONE */
  
  Timer timer;
  // initialize a pointer to what will later be the NGram
  NGramPolyApproach* n_gram = nullptr;

  while (true) {
    
    int option = query_input<int>(poly_approach_main_menu);
    
    switch (option) {
    case 0:
      std::cout << "Exiting..." << std::endl;
      return 0;

    case 1: {
      std::cout << "Creating shape..." << std::endl;
      // Ask for the number of main vertices that the NGram should have
      int num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      // Continue asking for the number of vertices until a valid answer is given.
      // The number of vertices must be greater than 3 in order to form an actual NGram.
      while (num_vertices < 3) {
	std::cout << "Number of vertices must be 3 or higher!" << std::endl;
	num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      }
      // Assign the now created NGram to the n_gram pointer.
      n_gram = new NGramPolyApproach(num_vertices);
      break;
    }

    case 2:
      std::cout << "Counting polygons..." << std::endl;
      if (n_gram == nullptr) {
	std::cout << "NO SHAPE DEFINED" << std::endl;
      }
      else {
	timer.start();
	long num_polys = n_gram->count_polys();
	std::cout << "Number of polygons: " << num_polys << std::endl;
	timer.stop();
	timer.display_time_passed();
      }
      break;

    case 3:
      std::cout << "Printing shape..." << std::endl;
      // Check if there is an NGram assigned to n_gram
      if (n_gram != nullptr) {
	// If there is an object, print NGram
	std::cout << n_gram->to_string() << std::endl;
      }
      else {
	// If the pointer is null, an NGram has not been created.
	std::cout << "Shape has not yet been created!" << std::endl;
      }
      break;

    default:
      std::cout << "Unknown input" << std::endl;
      break;
    }
  }
  delete n_gram;
  return 0;
}

int line_approach_loop() {
  Timer timer;
  // initialize a pointer to what will later be the NGram
  NGramLineApproach* n_gram = nullptr;
  // keeps track over whether the current n_gram has been fractured
  // this is necessary because they must be fractured to count without error
  bool fractured = false;

  while (true) {
    int option = query_input<int>(line_approach_main_menu);
    
    switch (option) {
    case 0:
      std::cout << "Exiting..." << std::endl;
      return 0;

    case 1: {
      std::cout << "Creating shape..." << std::endl;
      // Ask for the number of main vertices that the NGram should have
      int num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      // Continue asking for the number of vertices until a valid answer is given.
      // The number of vertices must be greater than 3 in order to form an actual NGram.
      while (num_vertices < 3) {
	std::cout << "Number of vertices must be 3 or higher!" << std::endl;
	num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      }
      // Assign the now created NGram to the n_gram pointer.
      n_gram = new NGramLineApproach(num_vertices);
      fractured = false;
      break;
    }

    case 2:
      std::cout << "Fracturing shape..." << std::endl;
      if (n_gram != nullptr) {
	timer.start();
	n_gram->fracture();
	fractured = true;
	timer.stop();
	timer.display_time_passed();
      }
      else {
	std::cout << "NO SHAPE DEFINED" << std::endl;
      }
      break;

    case 3:
      std::cout << "Counting polygons..." << std::endl;
      if (n_gram == nullptr) {
	std::cout << "NO SHAPE DEFINED" << std::endl;
      }
      else if (!fractured) {
	std::cout << "NGRAM HAS NOT BEEN FRACTURED" << std::endl;
      }
      else {
	timer.start();
	long num_polys = n_gram->count_polys();
	std::cout << "Number of polygons: " << num_polys << std::endl;
	timer.stop();
	timer.display_time_passed();
      }
      break;

    case 4:
      std::cout << "Printing shape..." << std::endl;
      // Check if there is an NGram assigned to n_gram
      if (n_gram != nullptr) {
	// If there is an object, print NGram
	std::cout << n_gram->to_string() << std::endl;
      }
      else {
	// If the pointer is null, an NGram has not been created.
	std::cout << "Shape has not yet been created!" << std::endl;
      }
      break;

    default:
      std::cout << "Unknown input" << std::endl;
      break;
    }
  }
  delete n_gram;
  return 0;
}

template <typename T>
T query_input(const std::string& prompt) {
  T input;
  while (true) {
    std::cout << prompt << std::endl;

    std::cin >> input;
    // Check if the input was successful
    if (std::cin) {
      // Break out of the loop if input is valid
      return input;
    }
    else {
      // Clear the error flag
      std::cin.clear();
      // Ignore the invalid input
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please try again." << std::endl;
    }
  }
}
