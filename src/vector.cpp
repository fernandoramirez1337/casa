#include <iostream>

#include "vector.hpp"

ogl::vector::vector(float x_, float y_, float z_)
                    : x(x_), y(y_), z(z_) {}

ogl::vector::vector(const ogl::vector& other)
                    : x(other.x), y(other.y), z(other.z) {}

ogl::vector::~vector() {}

std::ostream& ogl::operator<<(std::ostream& os, const ogl::vector& v) {
  os << "vector(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}