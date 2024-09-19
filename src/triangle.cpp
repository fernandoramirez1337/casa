#include "triangle.hpp"
#include "point.hpp"

ogl::triangle::triangle(const ogl::point& a_, const ogl::point& b_, const ogl::point& c_)
                       : a(a_), b(b_), c(c_) {}

ogl::triangle::triangle(const ogl::triangle& other)
                       : a(other.a), b(other.b), c(other.c) {}

ogl::triangle::~triangle() {}

void ogl::triangle::move(const ogl::vector& v) {
  a += v;
  b += v;
  c += v;
}

void ogl::triangle::get_vertices(float* vertices) const {
  vertices[0] = a.x; vertices[1] = a.y; vertices[2] = a.z;
  vertices[3] = b.x; vertices[4] = b.y; vertices[5] = b.z;
  vertices[6] = c.x; vertices[7] = c.y; vertices[8] = c.z;
}

void ogl::triangle::get_indices(unsigned int* indices, unsigned int base) const {
  float cross_product = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  if (cross_product < 0) {
    // Clockwise
    indices[0] = base; indices[1] = base + 1; indices[2] = base + 2;
  } else {
    // Counterclockwise
    indices[0] = base; indices[1] = base + 2; indices[2] = base + 1;
  }
}

std::vector<float> ogl::triangle::vertices() const {
  return {
    a.x, a.y, a.z,
    b.x, b.y, b.z,
    c.x, c.y, c.z
  };
}

std::vector<unsigned int> ogl::triangle::indices() const {
  std::vector<unsigned int> indices(3);
  float cross_product = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  
  if (cross_product < 0) {
    // Clockwise
    indices = { 0, 1, 2 };
  } else {
    // Counterclockwise
    indices = { 0, 2, 1 };
  }
  
  return indices;
}