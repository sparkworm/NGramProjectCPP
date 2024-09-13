#include <chrono>

class Timer {
 public:
  // Variables
  bool is_running;

  // Methods
  void start();
  void stop();
  double time_passed();
  void display_time_passed();
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time, stop_time;
};
