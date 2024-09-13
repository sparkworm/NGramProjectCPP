#include "Timer.h"

#include <iostream>

void Timer::start() {
  start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
  stop_time = std::chrono::high_resolution_clock::now();
}

double Timer::time_passed() {
  std::chrono::duration<double> d = stop_time - start_time;
  return d.count();
}

void Timer::display_time_passed() {
  std::cout << "Time passed: " << time_passed() << "s" << std::endl;
}
