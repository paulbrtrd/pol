
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "tools.h"
#include "parse_stl.h"

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



  std::ostream& operator<<(std::ostream& out, const Vertex p) {
    out << "(" << p.getx() << ", " << p.gety() << ", " << p.getz() << ")";
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Triangle& t) {
    out << "---- TRIANGLE ----" << std::endl;
    Vertex normal = t.getnormal();
    Vertex v1 = t.getv1();
    Vertex v2 = t.getv2();
    Vertex v3 = t.getv3();
    out << normal << std::endl;
    out << v1 << std::endl;
    out << v2 << std::endl;
    out << v3 << std::endl;
    return out;
  }

  bool operator==(const Vertex  v1, const Vertex  v2) {
  	return ( (v1.getx() == v2.getx()) && (v1.gety() == v2.gety()) && (v1.getz() == v2.getz()) );
  }

  bool operator==(const Triangle  t1, const Triangle  t2) {
  	return ( (t1.getv1_i() == t2.getv1_i()) && (t1.getv2_i() == t2.getv2_i()) && (t1.getv3_i() == t2.getv3_i()) && (t1.getnormal_i() == t2.getnormal_i()) );
  }

}
