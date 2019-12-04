#pragma once
#include "vertex.h"

namespace stl{
  float parse_float(std::ifstream& s);

  Vertex parse_vertex(std::ifstream& s);

  // Write the buffer for the vertex v
  void vertex_to_buf(char * buf, Vertex & v);
}
