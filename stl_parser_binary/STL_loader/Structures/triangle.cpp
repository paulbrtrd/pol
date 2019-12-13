#include "triangle.h"
#include <iostream>
#include "vertex.h"
namespace stl {

  /* Constructors */
    Triangle::Triangle(int normalp, int v1p, int v2p, int v3p, Stl_data * datap){
      normal_i = normalp;
  	  v1_i = v1p;
  	  v2_i = v2p;
  	  v3_i = v3p;
      data = datap;

    }

    Triangle::Triangle(Triangle * t) {
      normal_i = t->getnormal_i();
      v1_i = t->getv1_i();
      v2_i = t->getv2_i();
      v3_i = t->getv3_i();
    }

  /* Getters */
    Vertex Triangle::getv1() const
    {
      return (data->getvertices())->at(v1_i);
    }

    Vertex Triangle::getv2() const
    {
      return (data->getvertices())->at(v2_i);
    }

    Vertex Triangle::getv3() const
    {
      return (data->getvertices())->at(v3_i);
    }

    Vertex Triangle::getnormal() const
    {
      return (data->getnormals())->at(normal_i);
    }

    int Triangle::getv_i(int i) const {
      switch(i) {
        case 1:
          return v1_i;
        case 2:
          return v2_i;
        case 3:
          return v3_i;
        default:
          std::cout << "Error: in getv(): return normal" << std::endl;
          return normal_i;
      }
    }

    Vertex Triangle::getv(int i) const {
      switch(i) {
        case 1:
          return this->getv1();
        case 2:
          return this->getv2();
        case 3:
          return this->getv3();
        default:
          std::cout << "Error: in getv(): return normal" << std::endl;
          return this->getnormal();
      }
    }

    Vertex Triangle::getOrientation() {
      Vertex A = this->getv1();
      Vertex B = this->getv2();
      Vertex C = this->getv3();

      Vertex AB = A.vectorTo(B);
      Vertex AC = A.vectorTo(C);

      Vertex orientation = AB.crossProduct(AC);
      orientation.normalize();
      return orientation;
    }

    void Triangle::getLastVertices(int first_point, int * A, int * B) {
      if (v1_i == first_point) {
        *A = v2_i;
        *B = v3_i;
        return;
      }
      if (v2_i == first_point) {
        *A = v1_i;
        *B = v3_i;
        return;
      }
      if (v3_i == first_point) {
        *A = v1_i;
        *B = v2_i;
        return;
      }
      *A = -1;
      *B = -1;
    }

    void Triangle::decalVertices(int i) {
      if (v1_i > i) {
        v1_i --;
      }
      if (v2_i > i) {
        v2_i --;
      }
      if (v3_i > i) {
        v3_i --;
      }
    }

    bool operator==(const Triangle  t1, const Triangle  t2) {
      return ( (t1.getv1_i() == t2.getv1_i()) && (t1.getv2_i() == t2.getv2_i()) && (t1.getv3_i() == t2.getv3_i()) && (t1.getnormal_i() == t2.getnormal_i()) );
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
}
