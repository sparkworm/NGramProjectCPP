// The source code for the UI loop
#include "ui.h"

#include "NGram.h"

#include <iostream>
#include <limits>

std::string main_menu = std::string("What would you like to do?"
					  "\n\t0: Quit"
					  "\n\t1: Create Shape"
					  "\n\t2: Fracture shape"
					  "\n\t3: Count polygons"
					  "\n\t4: View shape");

int io_loop() {
  //NGram n_gram;
  while (true) {
    int option = query_input<int>(main_menu);
    switch (option) {
    case 0:
      std::cout << "Exiting..." << std::endl;
      return 0;
      break;
    case 1:
      std::cout << "Creating shape..." << std::endl;
      break;
    case 2:
      std::cout << "Fracturing shape..." << std::endl;
      break;
    case 3:
      std::cout << "Counting polygons..." << std::endl;
      break;
    case 4:
      std::cout << "Printing shape..." << std::endl;
      break;
    default:
      std::cout << "Unknown input" << std::endl;
      break;
    }
  }
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
