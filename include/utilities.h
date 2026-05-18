#ifndef CPURAYTRACER_INCLUDE_UTILITIES_H_
#define CPURAYTRACER_INCLUDE_UTILITIES_H_

#include <cmath>
#include <limits>
#include <random>

namespace math {

float
infinity() {
  return std::numeric_limits<float>::infinity();
}

float
pi() {
  return 3.1415926;
}

inline float
radians(float degrees) {
  return degrees * pi() / 180.0f;
}

inline float
random() {
  static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  static std::mt19937 generator;
  return distribution(generator);
}

inline float
random(float min, float max) {
  return min + (max-min+1)*random();
}

}

#include "../include/interval.h"
#include "../include/vec.h"
#include "../include/color.h"
#include "../include/ray.h"

#endif
