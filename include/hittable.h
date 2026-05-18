#ifndef CPURAYTRACER_INCLUDE_HITTABLE_H_
#define CPURAYTRACER_INCLUDE_HITTABLE_H_

#include "ray.h"


class HitRecord {
  public:
    Vec3 normal;
    Vec3 point;
    float t;

    void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
      bool frontFace = Vec3::dot(ray.direction(), outwardNormal) < 0; 
      normal = frontFace ? outwardNormal : -outwardNormal; // if normal is in same direction, flip normal
    }
};

class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, const Interval& interval, HitRecord& hitRecord) const = 0; // pure virtual function
};

#endif
