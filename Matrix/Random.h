#include <random>

#ifndef RANDOM_H
#define RANDOM_H

class Random {
public:
  Random();
  virtual ~Random() = default;
  virtual double Rand() = 0;
  static void ManualSeed(int seed);
};

class Gaussian : public Random {
public:
  virtual double Rand();
  virtual ~Gaussian() = default;

private:
  std::normal_distribution<double> mDist{0, 1};
};

class Uniform : public Random {
public:
  virtual double Rand();
  virtual ~Uniform() = default;

private:
  std::uniform_real_distribution<double> mDist{0, 1};
};

#endif
