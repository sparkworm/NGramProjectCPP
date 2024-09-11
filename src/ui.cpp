// The source code for the UI loop
#include "ui.h"

#include "NGram.h"
// might remove this later, it's only here for testing purposes at the moment
#include "utils.h"

#include <iostream>
#include <limits>

std::string main_menu = std::string("\n\nWhat would you like to do?"
				    "\n\t0: Quit"
				    "\n\t1: Create Shape"
				    "\n\t2: Fracture shape"
				    "\n\t3: Count polygons"
				    "\n\t4: View shape");

int io_loop() {
  point p1(100,0), p2(-0.00001,-100);
  point p3(0.0001,0.00001);

  line l1(p1,p2);

  int frfr = is_point_on_segment(p3, l1);
  
  std::cout << "Is point on line? " << frfr << std::endl;
  
  // initialize a pointer to what will later be the NGram
  NGram* n_gram = nullptr;

  while (true) {
    int option = query_input<int>(main_menu);
    
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
      n_gram = new NGram(num_vertices);
      break;
    }

    case 2:
      std::cout << "Fracturing shape..." << std::endl;
      if (n_gram != nullptr) {
	n_gram->fracture();
      }
      else {
	std::cout << "NO SHAPE DEFINED" << std::endl;
      }
      break;

    case 3:
      std::cout << "Counting polygons..." << std::endl;
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

// function fixed by ChatGPT :(
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
