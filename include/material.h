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


namespace material {
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

  class Metal : public Material {
    public:
      Metal(const Color& albedo, float fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}

      bool
      scatter(const Ray& incidentRay, HitRecord& hitRecord) {
        Vec3 reflectionDirection  = vector::utilities::reflect(incidentRay.direction(), hitRecord.normal);
        hitRecord.scatteredRay    = Ray(hitRecord.point, reflectionDirection);
        hitRecord.attenuation     = albedo_;
        return true;
      }

    private:
      Color albedo_;
      float fuzz_;
  };
}
#endif
