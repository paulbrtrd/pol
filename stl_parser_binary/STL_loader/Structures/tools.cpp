
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "tools.h"
#include "vertex.h"

namespace stl{
  float parse_float(std::ifstream& s) {
    char f_buf[sizeof(float)];
    s.read(f_buf, 4);
    float* fptr = (float*) f_buf;
    return *fptr;
   }


   Vertex parse_vertex(std::ifstream& s) {
    float x = parse_float(s);
    float y = parse_float(s);
    float z = parse_float(s);
    return Vertex(x, y, z);
  }

  void vertex_to_buf(char * buf, Vertex & v) {
    float x = v.getx();
    float y = v.gety();
    float z = v.getz();

    char * x_char = (char*) &x;
    char * y_char = (char*) &y;
    char * z_char = (char*) &z;

    int j=0;
    int i;
    for (i=0; i<4; i++) {
      buf[j] = x_char[i];
      j++;
    }
    for (i=0; i<4; i++) {
      buf[j] = y_char[i];
      j++;
    }
    for (i=0; i<4; i++) {
      buf[j] = z_char[i];
      j++;
    }
  }
}
