#ifndef CASA_HPP
#define CASA_HPP

#include "triangle.hpp"
#include "square.hpp"

namespace ogl {
class casa {
public:
  ogl::triangle techo;
  ogl::square pared;
  //ogl::square ventana_1, ventana_2;
  ogl::square puerta;
  unsigned int VBOs[3], VAOs[3], EBOs[3];
  casa();
  ~casa();

  void move(const ogl::vector&);

  void get_vertices(float*) const;
  void get_indices(unsigned int*, unsigned int = 0) const;
};
}

#endif