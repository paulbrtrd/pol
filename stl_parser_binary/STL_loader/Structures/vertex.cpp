#include "vertex.h"

#include <iostream>
#include <algorithm>

namespace stl {
  void Vertex::normalize() {
    float norm = this->norm();
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

  float Vertex::distanceTo(Vertex & v) {
    Vertex vect = this->vectorTo(v);
    float dist = vect.dot(vect)/(vect.norm());
    return dist;
  }

  float Vertex::distance_to_edge (Vertex & v1Edge, Vertex & v2Edge){
      stl::Vertex vect_directeur = v1Edge.vectorTo(v2Edge);
      stl::Vertex vect_v_v1Edge = v1Edge.vectorTo(*this);
      stl::Vertex vect_cross_prod = vect_directeur.crossProduct(vect_v_v1Edge);
      float norm_vect_directeur = vect_directeur.norm();
      float norm_vect_cross_prod = vect_cross_prod.norm();
      return norm_vect_cross_prod/norm_vect_directeur;
  }

  char Vertex::vertexType(int vertex_index, float *dist) {
    char vertex_type = 's';
    *dist = 0;
    float xm = 0;
    float ym = 0;
    float zm = 0;
    int nb_vertices = 0;
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
      if (i1==-1 || i2==-1) {
        std::cout << "ERREUR: getLastVertices a échoué pour le vertex " << vertex_index << "sur le triangle " << t << std::endl;
      }
      Vertex v1 = (data->getvertices())->at(i1);
      Vertex v2 = (data->getvertices())->at(i2);
      int nb_common_triangles_v1 = this->nbCommonTriangleWith(v1);
      int nb_common_triangles_v2 = this->nbCommonTriangleWith(v2);
      xm += v1.getx();
      ym += v1.gety();
      zm += v1.getz();
      nb_vertices++;
      xm += v2.getx();
      ym += v2.gety();
      zm += v2.getz();
      nb_vertices++;

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
      *dist= this->distance_to_edge((data->getvertices())->at(first_bound),(data->getvertices())->at(second_bound));
    }
    else if (first_bound != -1) {
      // Only one bound found --> complex vertex
      std::cout << "Only one bound found for " << *this << std::endl;
      vertex_type = 'c';
    }
    else {
      xm/=nb_vertices;
      ym/=nb_vertices;
      zm/=nb_vertices;
      Vertex vm = Vertex(xm,ym,zm);
      *dist = this->distanceTo(vm);
    }
    return vertex_type;
  }

  void Vertex::removeTriangle(int t) {
    std::vector<int>::iterator it = std::find(connected_triangles.begin(), connected_triangles.end(), t);
    if (it != connected_triangles.end()) {
      connected_triangles.erase(it);
    }
  }

  void Vertex::decalTriangles(int i_min) {
    for (int i=0; i < connected_triangles.size(); i++) {
      if (connected_triangles.at(i)>i_min) {
        connected_triangles.at(i)--;
      }
    }
  }

  bool operator==(const Vertex  v1, const Vertex  v2) {
    return ( (v1.getx() == v2.getx()) && (v1.gety() == v2.gety()) && (v1.getz() == v2.getz()) );
  }

  std::ostream& operator<<(std::ostream& out, const stl::Vertex& p) {
    out << "(" << p.getx() << ", " << p.gety() << ", " << p.getz() << ")";
    return out;
  }
}
