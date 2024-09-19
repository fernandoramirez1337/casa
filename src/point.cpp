#include "point.hpp"

ogl::point::point(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

ogl::point::point(const ogl::point& other) : x(other.x), y(other.y), z(other.z) {}

ogl::point::~point() {}

ogl::point& ogl::point::operator=(const ogl::point& other) {
  if (this != &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }
  return *this;
}

ogl::point& ogl::point::operator+=(const ogl::vector& v) {
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
  return *this;
}

ogl::point ogl::point::operator+(const ogl::vector& v) const {
  return ogl::point(this->x + v.x, this->y + v.y, this->z + v.z);
}

ogl::point& ogl::point::operator*=(float f) {
  this->x *= f;
  this->y *= f;
  this->z *= f;
  return *this;
}

ogl::point ogl::point::operator*(float f) const {
  return ogl::point(this->x * f, this->y * f, this->z * f);
}

std::ostream& ogl::operator<<(std::ostream& os, const ogl::point& v) {
  os << "point(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}
