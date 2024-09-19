#include "square.hpp"
#include "point.hpp"

#include <vector>

double signedArea(const ogl::point& p1, const ogl::point& p2, const ogl::point& p3) {
    return 0.5 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
}

ogl::square::square(const ogl::point& a_, const ogl::point& b_,
                    const ogl::point& c_, const ogl::point& d_) 
                    : a(a_), b(b_), c(c_), d(d_) {}

ogl::square::square(const ogl::square& other) 
                    : a(other.a), b(other.b),
                      c(other.c), d(other.d) {}

ogl::square::~square() {}

void ogl::square::move(const ogl::vector& v) {
  a += v;
  b += v;
  c += v;
  d += v;
}

void ogl::square::get_vertices(float* vertices) const {
  vertices[0] = a.x;  vertices[1] = a.y;  vertices[2] = a.z;
  vertices[3] = b.x;  vertices[4] = b.y;  vertices[5] = b.z;
  vertices[6] = c.x;  vertices[7] = c.y;  vertices[8] = c.z;
  vertices[9] = d.x; vertices[10] = d.y; vertices[11] = d.z;  
}

void ogl::square::get_indices(unsigned int* indices, unsigned int base) const {
  indices[0] = base; 
  indices[1] = base + 1;
  indices[2] = base + 2; 

  indices[3] = base;   
  indices[4] = base + 2;  
  indices[5] = base + 3;  
}

std::vector<float> ogl::square::vertices() const {
  return {
    a.x, a.y, a.z,
    b.x, b.y, b.z,
    c.x, c.y, c.z,
    d.x, d.y, d.z 
    };
}

std::vector<unsigned int> ogl::square::indices() const {
  return {
    0, 1, 2,
    0, 3, 2, 0, 3, 1, 2 
  };
}