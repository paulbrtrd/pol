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

    /* Browse the triangles connected to the current vertex */
    for(int & t1:connected_triangles) {
      /* Browse the triangles connected to the vertex v */
      for(int & t2: v_triangles) {
        /* If v and the current triangle have the same connected triangle index */
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

  float Vertex::distance_to_edge(Vertex & v1Edge, Vertex & v2Edge){
    /* Distance from vertex A to line (BC) can be computed
     * with: dist = norm(BC^BA)/norm(BC)
     * here: A = current vertex, B=v1Edge, C=v2Edge
     */
      Vertex BC = v1Edge.vectorTo(v2Edge);
      Vertex BA = v1Edge.vectorTo(*this);
      Vertex BCvBA = BC.crossProduct(BA);
      float norm_BC = BC.norm();
      float norm_BCvBA = BCvBA.norm();

      return norm_BCvBA/norm_BC;
  }

  char Vertex::vertexType(int vertex_index, float *dist) {
    // By default, the vertex_type is simple and the distance is -1
    char vertex_type = 's';
    *dist = -1;

    /* Variable used to compute the distance from the vertex to the average
     * point of its connected vertices */
    float xm = 0;
    float ym = 0;
    float zm = 0;
    int nb_vertices = 0;

    /* Variables used to store the bounds of the cycle */
    int first_bound = -1;
    int second_bound = -1;
    Vertex bound_1;
    Vertex bound_2;

    // Analyse each connected triangle
    for (int & i: connected_triangles){
      // Extract the current triangle
      Triangle t((data->gettriangles())->at(i));

      // Extract the 2 other vertices of the connected triangle
      int i1, i2;
      t.getLastVertices(vertex_index, &i1, &i2);
      if (i1==-1 || i2==-1) {
        std::cout << "ERREUR: getLastVertices a échoué pour le vertex " << vertex_index << "sur le triangle " << t << std::endl;
      }
      Vertex v1 = (data->getvertices())->at(i1);
      Vertex v2 = (data->getvertices())->at(i2);

      /* Compute the number of triangle that the current vertex has in common
       * with the other vertices */
      int nb_common_triangles_v1 = this->nbCommonTriangleWith(v1);
      int nb_common_triangles_v2 = this->nbCommonTriangleWith(v2);

      /* Update the average point coordinates */
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
            bound_1 = v1;
            first_bound = i1;
          }
          else if (second_bound == -1) {
            bound_2 = v2;
            second_bound = i1;
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
          continue;
        }
      }
    }

    /* Check wether the vertex is a boundary */
    if (second_bound != -1){
      // 2 bounds found --> boundary vertex
      vertex_type = 'b';
      *dist= distance_to_edge(bound_1, bound_2);
    }
    else if (first_bound != -1) {
      // Only one bound found --> complex vertex
      vertex_type = 'c';
    }
    else {
      /* Simple vertex. Finalize the computation of the average point and
       * compute the distance from the current vertex to this point */
      xm/=nb_vertices;
      ym/=nb_vertices;
      zm/=nb_vertices;
      Vertex vm = Vertex(xm,ym,zm);
      *dist = this->distanceTo(vm);
    }
    return vertex_type;
  }

  void Vertex::removeTriangle(int t) {
    // Look for the triangle index in the connected_triangle list */
    std::vector<int>::iterator it = std::find(connected_triangles.begin(), connected_triangles.end(), t);

    // If the triangle index is found, remove it from the list
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
