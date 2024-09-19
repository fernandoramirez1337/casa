#ifndef POINT_HPP
#define POINT_HPP

#include "vector.hpp"

#include <iostream>

namespace ogl {
class point {
public:
  float x, y, z;

  point(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f);
  point(const ogl::point& other);
  ~point();

  point& operator=(const ogl::point& other);
  point& operator+=(const ogl::vector& v);
  point operator+(const ogl::vector& v) const;
  point& operator*=(float f);
  point operator*(float f) const;

  friend std::ostream& operator<<(std::ostream& os, const ogl::point& v);
};
}

#endif