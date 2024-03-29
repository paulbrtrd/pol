/*
 * Classe Triangles. Elle stocke les indices des vertices/normales dans l'instance de Stl_data auquelle elle est associée.
 * La surcharge des opérateur << et == sont écrits ici également.
 */

#pragma once
#include "stl_data.h"
#include "vertex.h"

namespace stl {
  class Stl_data;
  class Vertex;
  class Triangle {
  private:
    /* Indexes of the normal, v1, v2, and v3 in the vertices and normal list */
    int normal_i;
    int v1_i;
    int v2_i;
    int v3_i;

    /* Pointer to the Stl_data the triangle belongs */
    Stl_data * data;

  public:
    Triangle(int normalp, int v1p, int v2p, int v3p, Stl_data * datap);
    Triangle(Triangle * t);

    /* Return the index of the vertex or normal in the list */
    int getv1_i() const { return v1_i; };
    int getv2_i() const { return v2_i; };
    int getv3_i() const { return v3_i; };
    int getv_i(int i) const;
    int getnormal_i() const { return normal_i; };

    /* Return the Stl_data associated to the triangle */
    Stl_data * getdata(){ return data; };

    /* Return a COPY of the vertex or normal */
    Vertex getv1() const;
    Vertex getv2() const;
    Vertex getv3() const;
    Vertex getnormal() const;
    Vertex getv(int i) const;

    /* Return the vector AB^AC (<=>v1v2^v1v3) normalized,
     * for a triangle ABC (<=> v1v2v3) */
    Vertex getOrientation();

    /* Return the 2 other vertices of the triangle, if first_point is in the triangle.
     * Set -1 to A and B if not.
     */
    void getLastVertices(int first_point, int * A, int * B);

    /* Decrement the index greater than i */
    void decalVertices(int i);
  };
  /*
   * Surcharge de == pour les triangles.
   * Le test est effectué seulement sur l'indice des vertices.
   * L'égalité du data relié au triangle n'est pas testée.
  */
  bool operator==(const Triangle  t1, const Triangle  t2);
  
  // Surcharge de l'opérateur << pour l'affichage des informations d'un triangle
  std::ostream& operator<<(std::ostream& out, const Triangle& t);
}
