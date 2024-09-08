// The source code for the UI loop
#include "ui.h"

#include "NGram.h"

#include <iostream>
#include <limits>

std::string main_menu = std::string("\n\nWhat would you like to do?"
				    "\n\t0: Quit"
				    "\n\t1: Create Shape"
				    "\n\t2: Fracture shape"
				    "\n\t3: Count polygons"
				    "\n\t4: View shape");

int io_loop() {
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
      int num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      while (num_vertices < 3) {
	std::cout << "Number of vertices must be 3 or higher!" << std::endl;
	num_vertices = query_input<int>(std::string("How many vertices would you like?\n"));
      }
      n_gram = new NGram(num_vertices);
      break;
    }
    case 2:
      std::cout << "Fracturing shape..." << std::endl;
      break;
    case 3:
      std::cout << "Counting polygons..." << std::endl;
      break;
    case 4:
      std::cout << "Printing shape..." << std::endl;
      if (n_gram != nullptr) {
	std::cout << n_gram->to_string() << std::endl;
      }
      else {
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

/*
template <typename T>
T query_input(std::string prompt) {
  std::cout << prompt << std::endl << std::endl;
  T input;
  return input;
}
*/

// function fixed by ChatGPT :(
template <typename T>
T query_input(const std::string& prompt) {
  T input;
  while (true) {
    std::cout << prompt << std::endl;

    // CAUSES SEGFAULT
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
