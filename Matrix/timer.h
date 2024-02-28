#include <chrono>

#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
  Timer() = default;
  void Tic();
  double Toc();

private:
  std::chrono::high_resolution_clock mClock;
  std::chrono::time_point<std::chrono::high_resolution_clock> mCheckpoint;
  std::chrono::duration<double> mElapsed;
};

#endif
