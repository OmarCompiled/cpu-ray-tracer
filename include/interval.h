#ifndef CPURAYTRACER_INCLUDE_INTERVAL_H_
#define CPURAYTRACER_INCLUDE_INTERVAL_H_

struct Interval {
  const float min;
  const float max;

  Interval() : min(math::infinity()), max(-math::infinity()) {}
  Interval(float min, float max) : min(min), max(max) {}

  float size() const {
    return max - min;
  }

  bool contains(float x) const {
    return (x >= min && x <= max);
  }

  bool surrounds(float x) const {
    return (x > min && x < max);
  }

  static const Interval empty;     
  static const Interval universe;  
};

const Interval Interval::empty    {math::infinity(), -math::infinity()};
const Interval Interval::universe {-math::infinity(), math::infinity()};
#endif
