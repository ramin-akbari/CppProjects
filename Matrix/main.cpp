#include "Matrix.h"
#include "Random.h"
#include "timer.h"
#include <iostream>

int main() {

  Random::ManualSeed(0);
  Timer timer;
  Matrix a(3000, 3000, true);
  Matrix b(3000, 3000, true);

  timer.Tic();
  a.transpose();
  std::cout << timer.Toc() << " seconds elapsed for transpose \n";

  timer.Tic();
  auto c = a * b;
  std::cout << timer.Toc() << " seconds elapsed for matrix multiplication \n";
  std::cout << c(10, 15) << "\n";
  return 0;
}
