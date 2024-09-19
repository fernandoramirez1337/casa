#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>

#include "point.hpp"
#include "vector.hpp"

namespace ogl {
class triangle {
public:
  ogl::point a, b, c;
  triangle(const ogl::point&, const ogl::point&, const ogl::point&);
  triangle(const ogl::triangle&);
  ~triangle();

  void move(const ogl::vector&);
  void scale(const float);
  //void rotate(const ogl::vector&);

  void get_vertices(float*) const;
  void get_indices(unsigned int*, unsigned int = 0) const;

  std::vector<float> vertices() const;
  std::vector<unsigned int> indices() const;

};
}

#endif