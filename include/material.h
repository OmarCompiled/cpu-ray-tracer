#ifndef CPURAYTRACER_INCLUDE_MATERIAL_H_
#define CPURAYTRACER_INCLUDE_MATERIAL_H_

#include "hittable.h"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool
    scatter(const Ray& incidentRay, HitRecord& hitRecord) {
      return false; 
    }
};

class Lambertian : public Material {
  public:
    Lambertian(const Color& albedo) : albedo_(albedo) {}

    bool
    scatter(const Ray& incidentRay, HitRecord& hitRecord) {
      Vec3 scatterDirection   = hitRecord.normal + vector::utilities::randomUnitVector();
      if(scatterDirection == Vec3::zero) {
        scatterDirection = hitRecord.normal;
      }

      hitRecord.scatteredRay  = Ray(hitRecord.point, scatterDirection);
      hitRecord.attenuation   = albedo_;
      return true;
    }

  private:
    Color albedo_;
};

#endif
