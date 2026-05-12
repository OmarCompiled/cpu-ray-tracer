#pragma once

#include "vec.h"

class ray {
public:
  ray() {}
  ray(const vec3& origin, const vec3& direction) : m_Origin(origin), m_Direction(direction) {}

  const vec3& origin() const {return m_Origin;}
  const vec3& direction() const {return m_Direction;}

  vec3 at(float t) const {
    return m_Origin + (t * m_Direction);
  }

private:
  vec3 m_Origin;
  vec3 m_Direction;
};
