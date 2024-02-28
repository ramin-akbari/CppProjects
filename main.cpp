#include "Matrix.h"
#include <chrono>
#include <iostream>

int main() {
  // Matrix a(3000, 3000, true);
  // Matrix b(3000, 3000, true);
  // auto st = std::chrono::high_resolution_clock::now();
  // a.transpose();
  // auto end = std::chrono::high_resolution_clock::now();
  // auto c = a * b;
  // auto elapsed =
  //     std::chrono::duration_cast<std::chrono::microseconds>(end - st);
  // std::cout << elapsed.count() / 1e3 << "ms \n";
  // std::cout << c(10, 15) << "\n";
  Matrix a(3, 5, true);
  (a >> std::cout) << "\n";
  a.transpose();
  (a >> std::cout) << "\n";
  return 0;
}
