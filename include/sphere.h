#ifndef CPURAYTRACER_INCLUDE_SPHERE_H_
#define CPURAYTRACER_INCLUDE_SPHERE_H

#include <cmath>

#include "hittable.h"

class Sphere : public Hittable {
  public:
    Sphere(const Vec3& center, float radius) : center_(center), radius_(std::fmax(0, radius)) {};
  
    bool hit(const Ray& ray, const Interval& interval, HitRecord& hitRecord) const override {
      Vec3 qc = center_ - ray.origin(); // qc arbitrary name; convention in mathematics (point p, q, etc...)
      float a = ray.direction().lengthSquared();
      float h = Vec3::dot(qc, ray.direction()); // h = b / -2.0f
      float c = qc.lengthSquared() - radius_ * radius_;
      float discriminant = h*h - a*c;
      if(discriminant < 0) {
        return false;
      }

      float sqrtDiscriminant = std::sqrt(discriminant);

      float root = (h - sqrtDiscriminant) / a;
      if(!interval.surrounds(root)) {
        root = (h + sqrtDiscriminant) / a;
        if(!interval.surrounds(root)) {
          return false;
        }
      }

      Vec3 outwardNormal;

      hitRecord.t = root;
      hitRecord.point = ray.at(hitRecord.t);
      outwardNormal = (hitRecord.point - center_).normalized();
      hitRecord.setFaceNormal(ray, outwardNormal);

      return true;
    }

  private:
    Vec3 center_;
    float radius_;
};

#endif
