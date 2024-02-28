#include <random>

class Random {
public:
  Random();
  virtual ~Random() = default;
  virtual double Rand() = 0;
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
