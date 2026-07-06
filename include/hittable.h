#ifndef CPURAYTRACER_INCLUDE_HITTABLE_H_
#define CPURAYTRACER_INCLUDE_HITTABLE_H_

#include <memory>

#include "ray.h"

class Material;

class HitRecord {
  public:
    Vec3 normal;
    Vec3 point;
    std::shared_ptr<Material> material;
    // bundled attemuation and scatteredRay here to decrease no. of
    // function parameters;
    Color attenuation;
    Ray scatteredRay;
    bool frontFace;
    float t;

    void
    setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
      frontFace = Vec3::dot(ray.direction(), outwardNormal) < 0; 
      normal = frontFace ? outwardNormal : -outwardNormal; // if normal is in same direction, flip normal
    }
};

class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool 
    hit(const Ray& ray, const Interval& interval, HitRecord& hitRecord) const = 0; // pure virtual function
};

#endif
