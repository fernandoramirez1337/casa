#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <vector>

#include "point.hpp"
#include "vector.hpp"

namespace ogl {
class square {
public:
  ogl::point a, b, c, d;
  square(const ogl::point&, const ogl::point&, const ogl::point&, const ogl::point&);
  square(const ogl::square&);
  ~square();

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