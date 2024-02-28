#include <chrono>

class Timer {
public:
  Timer();
  void Tic();
  double Toc();

private:
  std::chrono::high_resolution_clock mCheckpoint;
  std::chrono::duration<double> mElapsed;
}
