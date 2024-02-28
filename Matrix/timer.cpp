#include "timer.h"

void Timer::Tic() { mCheckpoint = mClock.now(); }

double Timer::Toc() {
  mElapsed = mClock.now() - mCheckpoint;
  return mElapsed.count();
}
