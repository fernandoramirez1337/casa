#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace ogl {
class vector {
public:
  float x, y, z;

  vector(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f);
  vector(const ogl::vector&);
  ~vector();

  friend std::ostream& operator<<(std::ostream& os, const ogl::vector& v);
};
}

#endif