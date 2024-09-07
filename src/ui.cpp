// The source code for the UI loop
#include <iostream>
#include "ui.h"

std::string main_menu = std::string("What would you like to do?"
				    "\n\t0: Quit"
				    "\n\t1: Create Shape"
				    "\n\t2: Fracture shape"
				    "\n\t3: Count polygons"
				    "\n\t4: View shape");

int io_loop() {
  while (true) {
    int option = query_input<int>(main_menu);
    switch (option) {
    case 0:
      std::cout << "Exiting..." << std::endl;
      return 0;
      break;
    default:
      std::cout << "Unknown input" << std::endl;
      break;
    }
  }
  return 0;
}

template <typename T>
T query_input(std::string prompt) {
  std::cout << prompt << std::endl << std::endl;
  T input;
  std::cin >> input;
  return input;
}
