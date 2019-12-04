#include "vertex.h"
#include <cmath>
#include <iostream>
namespace stl {
  void Vertex::normalize() {
    float norm = std::sqrt(x*x + y*y + z*z);
    x/=norm;
    y/=norm;
    z/=norm;
  }

  bool operator==(const Vertex  v1, const Vertex  v2) {
    return ( (v1.getx() == v2.getx()) && (v1.gety() == v2.gety()) && (v1.getz() == v2.getz()) );
  }

  std::ostream& operator<<(std::ostream& out, const stl::Vertex& p) {
    out << "(" << p.getx() << ", " << p.gety() << ", " << p.getz() << ")";
    return out;
  }
}
