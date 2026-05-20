#ifndef CPURAYTRACER_INCLUDE_HITTABLE_LIST_H_
#define CPURAYTRACER_INCLUDE_HITTABLE_LIST_H_

#include <initializer_list>
#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable {
  public:
    std::vector<std::shared_ptr<Hittable>> objects;
  
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) {add(object);}
    HittableList(std::initializer_list<std::shared_ptr<Hittable>> list) {
      add(list);
    }

    void 
    add(std::shared_ptr<Hittable> object) {
      objects.push_back(object);
    }

    void
    add(std::initializer_list<std::shared_ptr<Hittable>> list) {
      for(std::shared_ptr<Hittable> object : list) {
        add(object);
      }
    }

    void
    clear() {
      objects.clear();
    }

    bool
    hit(const Ray& ray, const Interval& interval, HitRecord& hitRecord) const override {
      HitRecord tempHitRecord;
      bool hitAnything = false;
      float closestSoFar = interval.max;

      for(const auto& object : objects) {
        if(object->hit(ray, Interval(interval.min, closestSoFar), tempHitRecord)) {
          hitAnything = true;
          closestSoFar = tempHitRecord.t;
          hitRecord = tempHitRecord;
        }
      }

      return hitAnything;
    }
};

#endif
