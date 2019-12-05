#include "vertex.h"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace stl {
  void Vertex::normalize() {
    float norm = std::sqrt(x*x + y*y + z*z);
    x/=norm;
    y/=norm;
    z/=norm;
  }

  int Vertex::nbCommonTriangleWith(Vertex &v) {
    int result = 0;
    std::vector<int> v_triangles = v.get_connected_triangle();
    for(int & t1:connected_triangles) {
      for(int & t2: v_triangles) {
        if (t1 == t2) {
          result++;
        }
      }
    }
    return result;
  }

  char Vertex::vertexType(int vertex_index) {
    char vertex_type = 's';

    std::vector<stl::Triangle> connected_triang;
    // create connected_triangles vector with Triangle objects
    for (int & i: connected_triangles){
      stl::Triangle t((data->gettriangles())->at(i));
      connected_triang.push_back(t);
    }

    /* Variables to store the bounds of the cycle */
    int first_bound = -1;
    int second_bound = -1;

    // Analyse each connected triangle
    for (stl::Triangle t:connected_triang){
      int i1, i2; // Indexes of the 2 other vertices of the connected triangle
      t.getLastVertices(vertex_index, &i1, &i2);
      Vertex v1 = (data->getvertices())->at(i1);
      Vertex v2 = (data->getvertices())->at(i2);
      int nb_common_triangles_v1 = this->nbCommonTriangleWith(v1);
      int nb_common_triangles_v2 = this->nbCommonTriangleWith(v2);


      if ( (nb_common_triangles_v1 != 2) || (nb_common_triangles_v2 != 2) ) {
        /*
         * If the current vertex has only 1 triangle in common with each of v1
         * and v2, it means it is a complex vertex.
         */
        if ( (nb_common_triangles_v1 == 1) && (nb_common_triangles_v2 == 1) ) {
          // The 2 vertices are alone --> complex vertex
          vertex_type = 'c';
          return vertex_type;
        }

        /* If there are more than 2 triangles in common --> complex vertex */
        if ( (nb_common_triangles_v1 > 2) || (nb_common_triangles_v2 > 2) ) {
          vertex_type = 'c';
          return vertex_type;
        }

        /*
         * If the current vertex and v1 has only 1 triangle in common while
         * there are 2 common triangles for v2, it means v1 is a bound.
         * Same thing for v2.
         */
        if( (nb_common_triangles_v1 == 1) && (nb_common_triangles_v2 == 2) ) {
          // v1 is a bound
          if(first_bound == -1) {
            first_bound = i1;
          }
          else if (second_bound == -1) {
            second_bound = i1;
          }
          else {
            std::cout << "ERROR1: 3 bounds found for " << *this << std::endl;
          }
          continue;
        }
        if( (nb_common_triangles_v2 == 1) && (nb_common_triangles_v1 == 2) ) {
          // v2 is a bound
          if(first_bound == -1) {
            first_bound = i2;
          }
          else if (second_bound == -1) {
            second_bound = i2;
          }
          else {
            std::cout << "ERROR2: 3 bounds found for " << *this << std::endl;
          }
          continue;
        }
      }
    }

    /* Check wether the vertex is a boundary */
    if (second_bound != -1){
      // 2 bounds found --> boundary vertex
      vertex_type = 'b';
    }
    else if (first_bound != -1) {
      // Only one bound found --> complex vertex
      std::cout << "Only one bound found for " << *this << std::endl;
      vertex_type = 'c';
    }

    return vertex_type;
  }

  bool operator==(const Vertex  v1, const Vertex  v2) {
    return ( (v1.getx() == v2.getx()) && (v1.gety() == v2.gety()) && (v1.getz() == v2.getz()) );
  }

  std::ostream& operator<<(std::ostream& out, const stl::Vertex& p) {
    out << "(" << p.getx() << ", " << p.gety() << ", " << p.getz() << ")";
    return out;
  }
}
