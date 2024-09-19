#include "casa.hpp"

#include <cstring> 

ogl::casa::casa() : 
pared(ogl::point(-0.15f, 0.25f, 0.0f), ogl::point( 0.15f, 0.25f, 0.0f),
      ogl::point( 0.15f,-0.25f, 0.0f), ogl::point(-0.15f,-0.25f, 0.0f)),
techo(ogl::point( 0.00f, 0.50f, 0.0f), ogl::point( 0.25f, 0.25f, 0.0f), 
      ogl::point(-0.25f, 0.25f, 0.0f)),
puerta(ogl::point(-0.06f, 0.00f, 0.0f), ogl::point( 0.06f, 0.00f, 0.0f),
       ogl::point( 0.06f,-0.25f, 0.0f), ogl::point(-0.06f,-0.25f, 0.0f)) { }

ogl::casa::~casa() { }

void ogl::casa::move(const ogl::vector& v) {
  pared.move(v);
  techo.move(v);
  puerta.move(v);
}

void ogl::casa::get_vertices(float* vertices) const {
  float techoVertices[9];
  techo.get_vertices(techoVertices);
  std::memcpy(vertices, techoVertices, 9 * sizeof(float));

  float paredVertices[12];
  pared.get_vertices(paredVertices);
  std::memcpy(vertices + 9, paredVertices, 12 * sizeof(float));  

  float puertaVertices[12];
  puerta.get_vertices(puertaVertices);
  std::memcpy(vertices + 21, puertaVertices, 12 * sizeof(float)); 
}

void ogl::casa::get_indices(unsigned int* indices, unsigned int base) const {
  unsigned int indicesTecho[3];
  techo.get_indices(indicesTecho);
  std::memcpy(indices, indicesTecho, 3 * sizeof(unsigned int));

  unsigned int indicesPared[6];
  pared.get_indices(indicesPared, 3);
  std::memcpy(indices + 3, indicesPared, 6 * sizeof(unsigned int));

  unsigned int indicesPuerta[6];
  puerta.get_indices(indicesPuerta, 9);
  std::memcpy(indices + 9, indicesPuerta, 6 * sizeof(unsigned int));
}

