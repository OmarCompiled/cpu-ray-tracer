#ifndef CPURAYTRACER_INCLUDE_RAY_H_
#define CPURAYTRACER_INCLUDE_RAY_H_

#include "../include/utilities.h"
#include "../include/vec.h"

class Ray {
public:
  Ray() {}
  Ray(const Vec3& origin, const Vec3& direction) : origin_(origin), direction_(direction) {}

  const Vec3& 
  origin() const {return origin_;}

  const Vec3& 
  direction() const {return direction_;}

  Vec3
  at(float t) const {
    return origin_ + (t * direction_);
  }

private:
  Vec3 origin_;
  Vec3 direction_;
};

#endif
