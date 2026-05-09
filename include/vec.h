#pragma once

#include <array> // much safer
#include <cmath>

class vec3 {
  public:
    std::array<float, 3> e; // e is the generalized notation for dimensions
                            // so x, y, z ==> e1, e2, e3; etc.

    vec3() : e{0.0f, 0.0f, 0.0f} {}
    vec3(float e1, float e2, float e3) : e{e1, e2, e3} {}
    vec3(float value) : e{value, value, value} {}

    float x() const {return e[0];}
    float y() const {return e[1];}
    float z() const {return e[2];}

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    float operator[](int i) const {return e.at(i);} // this will throw an exception on invalid i;
    float& operator[](int i) {return e.at(i);}

    vec3& operator+=(const vec3& v) {
      e[0] += v[0];
      e[1] += v[1];
      e[2] += v[2];
      return *this;
    }

    vec3& operator*=(float s) {
      e[0] *= s;
      e[1] *= s;
      e[2] *= s;
      return *this;
    }

    vec3& operator/=(float s) {
      return *this *= 1.0f/s;
    }

    float length() const {
      return std::sqrt(this->length_squared());
    }

    float length_squared() const {
      return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    
    vec3 operator/(float s) const {
      return vec3(e[0]/s, e[1]/s, e[2]/s);
    }
  
    vec3 normalized() {
      return *this / this->length();
    };
};

class vec4 {
  public:
    std::array<float, 4> e;

    vec4() : e{0.0f, 0.0f, 0.0f, 0.0f} {}
    vec4(float e1, float e2, float e3, float e4) : e{e1, e2, e3, e4} {}
    vec4(float value) : e{value, value, value, value} {}
    vec4(const vec3& v, float e4) : e{v[0], v[1], v[2], e4} {}

    float x() const {return e[0];}
    float y() const {return e[1];}
    float z() const {return e[2];}
    float w() const {return e[3];}

    vec4 operator-() const {return vec4(-e[0], -e[1], -e[2], -e[3]);}
    float operator[](int i) const {return e.at(i);}
    float& operator[](int i) {return e.at(i);}

    vec4 operator+=(vec4 v) {
      e[0] += v[0];
      e[1] += v[1];
      e[2] += v[2];
      e[3] += e[3];
      return *this;
    }

    vec4& operator*=(float s) {
      e[0] *= s;
      e[1] *= s;
      e[2] *= s;
      e[3] *= s;
      return *this;
    }

    vec4& operator/=(float s) {
      return *this *= 1.0f/s; 
    }

    float length() const {
      return std::sqrt(this->length_squared()); 
    }

    float length_squared() const {
      return e[0] * e[0] + e[1] * e[1]
        + e[2] * e[2] + e[3] * e[3];
    }

    vec4 operator/(float s) const {
      return vec4(e[0]/s, e[1]/s, e[2]/s, e[3]/s);
    }
  
    vec4 normalized() {
      return *this / this->length();
    };

};

inline vec3 operator+(const vec3& v, const vec3& u) {
  return vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}

inline vec4 operator+(const vec4& v, const vec4& u) {
  return vec4(v[0] + u[0], v[1] + u[1], v[2] + u[2], v[3] + u[3]);
}

inline vec3 operator-(const vec3& v, const vec3& u) {
  return vec3(v[0] - u[0], v[1] - u[1], v[2] - u[2]);
}

inline vec4 operator-(const vec4& v, const vec4& u) {
  return vec4(v[0] + u[0], v[1] + u[1], v[2] + u[2], v[3] + u[3]);
}

// component-wise vector multiplication; NOT dot product
inline vec3 operator*(const vec3& v, const vec3& u) {
  return vec3(v[0] * u[0], v[1] * u[1], v[2] * u[2]);
}

inline vec4 operator*(const vec4& v, const vec4& u) {
  return vec4(v[0] * u[0], v[1] * u[1], v[2] * u[2], v[3] * u[3]);
}

inline vec3 operator*(float s, const vec3& v) {
  return vec3(s*v[0], s*v[1], s*v[2]);
}

inline vec3 operator*(const vec3& v, float s) {
  return s * v;
}

inline vec4 operator*(float s, const vec4& v) {
  return vec4(s*v[0], s*v[1], s*v[2], s*v[3]);
}

inline vec4 operator*(const vec4& v, float s) {
  return s * v;
}

inline vec3 operator/(const vec3& v, float s) {
  return (1/s) * v;
}

inline vec4 operator/(const vec4& v, float s) {
  return (1/s) * v;
}

inline float dot(const vec3& v, const vec3& u) {
  return  v[0] * u[0] 
        + v[1] * u[1] 
        + v[2] * u[2];
}

inline float dot(const vec4& v, const vec4& u) {
  return  v[0] * u[0] 
        + v[1] * u[1] 
        + v[2] * u[2] 
        + v[3] * u[3];
}

inline vec3 cross(const vec3& v, const vec3& u) {
  return vec3(v[1] * u[2] - v[2] * u[1],
              v[2] * u[0] - v[0] * u[2],
              v[0] * u[1] - v[1] * u[0]);
}
