#include "Random.h"

std::default_random_engine gen(time(NULL));

void Random::ManualSeed(int seed) { gen.seed(seed); }

Random::Random() {}

double Gaussian::Rand() { return mDist(gen); }
double Uniform::Rand() { return mDist(gen); }
