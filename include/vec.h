#ifndef CPURAYTRACER_INCLUDE_VEC_H_
#define CPURAYTRACER_INCLUDE_VEC_H_

#include <array> // much safer
#include <cmath>

class Vec3 {
  private:
    std::array<float, 3> e_; // e is the generalized notation for dimensions
                            // so x, y, z ==> e1, e2, e3; etc.
  public:

    Vec3() : e_{0.0f, 0.0f, 0.0f} {}
    Vec3(float e1, float e2, float e3) : e_{e1, e2, e3} {}
    Vec3(float value) : e_{value, value, value} {}

    float x() const {return e_[0];}
    float y() const {return e_[1];}
    float z() const {return e_[2];}

    Vec3 operator-() const {return Vec3(-e_[0], -e_[1], -e_[2]);}
    float operator[](int i) const {return e_.at(i);} // this will throw an exception on invalid i;
    float& operator[](int i) {return e_.at(i);}
    
    bool operator==(const Vec3& other) {
      float diffX = std::abs(other.x() - x());
      float diffY = std::abs(other.y() - y());
      float diffZ = std::abs(other.z() - z());
      if(diffX <= 1e-5 && diffY <= 1e-5 && diffZ <= 1e-5) {
        return true;
      }

      return false;
    }

    Vec3& operator+=(const Vec3& v) {
      e_[0] += v[0];
      e_[1] += v[1];
      e_[2] += v[2];
      return *this;
    }

    Vec3& operator*=(float s) {
      e_[0] *= s;
      e_[1] *= s;
      e_[2] *= s;
      return *this;
    }

    Vec3& operator/=(float s) {
      return *this *= 1.0f/s;
    }

    float length() const {
      return std::sqrt(this->lengthSquared());
    }

    float lengthSquared() const {
      return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
    }

    static Vec3 i() {
      return Vec3(1.0f, 0.0f, 0.0f);
    }

    static Vec3 j() {
      return Vec3(0.0f, 1.0f, 0.0f);
    }

    static Vec3 k() {
      return Vec3(0.0f, 0.0f, 1.0f);
    }

    static float dot(const Vec3& v, const Vec3& u) {
      return  v[0] * u[0] 
        + v[1] * u[1] 
        + v[2] * u[2]; 
    }

    static Vec3 cross(const Vec3& v, const Vec3& u) {
      return Vec3(v[1] * u[2] - v[2] * u[1],
          v[2] * u[0] - v[0] * u[2],
          v[0] * u[1] - v[1] * u[0]);
    }

    Vec3 normalized() const;

    static const Vec3 right;
    static const Vec3 up;
    static const Vec3 forward ;
};

const Vec3 Vec3::right    = Vec3::i();
const Vec3 Vec3::up       = Vec3::j();
const Vec3 Vec3::forward  = Vec3::k();

class Vec4 {
  private:
    std::array<float, 4> e_;

  public:
    Vec4() : e_{0.0f, 0.0f, 0.0f, 0.0f} {}
    Vec4(float e1, float e2, float e3, float e4) : e_{e1, e2, e3, e4} {}
    Vec4(float e) : e_{e, e, e, e} {}
    Vec4(const Vec3& v, float e4) : e_{v[0], v[1], v[2], e4} {}

    float x() const {return e_[0];}
    float y() const {return e_[1];}
    float z() const {return e_[2];}
    float w() const {return e_[3];}

    Vec4 operator-() const {return Vec4(-e_[0], -e_[1], -e_[2], -e_[3]);}
    float operator[](int i) const {return e_.at(i);}
    float& operator[](int i) {return e_.at(i);}

    Vec4 operator+=(Vec4 v) {
      e_[0] += v[0];
      e_[1] += v[1];
      e_[2] += v[2];
      e_[3] += v[3];
      return *this;
    }

    Vec4& operator*=(float s) {
      e_[0] *= s;
      e_[1] *= s;
      e_[2] *= s;
      e_[3] *= s;
      return *this;
    }

    Vec4& operator/=(float s) {
      return *this *= 1.0f/s; 
    }

    float length() const {
      return std::sqrt(this->lengthSquared()); 
    }

    float lengthSquared() const {
      return e_[0] * e_[0] + e_[1] * e_[1]
        + e_[2] * e_[2] + e_[3] * e_[3];
    }

    float dot(const Vec3& v, const Vec3& u) {
      return  v[0] * u[0] 
        + v[1] * u[1] 
        + v[2] * u[2]
        + v[3] * u[3];
    }

    Vec4 normalized() const;
};

/* Vec3 */

inline Vec3 operator+(const Vec3& v, const Vec3& u) {
  return Vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}

inline Vec3 operator-(const Vec3& v, const Vec3& u) {
  return Vec3(v[0] - u[0], v[1] - u[1], v[2] - u[2]);
}

inline Vec3 operator*(float s, const Vec3& v) {
  return Vec3(s*v[0], s*v[1], s*v[2]);
}

inline Vec3 operator*(const Vec3& v, float s) {
  return s * v;
}

inline Vec3 operator/(const Vec3& v, float s) {
  return (1/s) * v;
}

// component-wise Vector multiplication; NOT dot product
inline Vec3 operator*(const Vec3& v, const Vec3& u) {
  return Vec3(v[0] * u[0], v[1] * u[1], v[2] * u[2]);
}

/* Vec4 */

inline Vec4 operator+(const Vec4& v, const Vec4& u) {
  return Vec4(v[0] + u[0], v[1] + u[1], v[2] + u[2], v[3] + u[3]);
}

inline Vec4 operator-(const Vec4& v, const Vec4& u) {
  return Vec4(v[0] - u[0], v[1] - u[1], v[2] - u[2], v[3] - u[3]);
}

inline Vec4 operator*(const Vec4& v, const Vec4& u) {
  return Vec4(v[0] * u[0], v[1] * u[1], v[2] * u[2], v[3] * u[3]);
}

inline Vec4 operator*(float s, const Vec4& v) {
  return Vec4(s*v[0], s*v[1], s*v[2], s*v[3]);
}

inline Vec4 operator*(const Vec4& v, float s) {
  return s * v;
}

inline Vec4 operator/(const Vec4& v, float s) {
  return (1/s) * v;
}

Vec3 Vec3::normalized() const {
  return *this/this->length();
}

Vec4 Vec4::normalized() const {
  return *this/this->length();
}

#endif
