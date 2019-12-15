/* Classe Vertex.
 * Les triangles connectés au vertex sont stockés sous forme d'indice dans
 * le Stl_data associé au Vertex.
 */
#pragma once
#include "stl_data.h"
#include <cmath>

namespace stl {
  class Stl_data;
  class Vertex {
  private:
    float x;
    float y;
    float z;

    /* Indexes of the connected triangle in the list of triangle */
    std::vector<int> connected_triangles;

    /* Pointer to the Stl_data the vertex belongs */
    Stl_data * data;

  public:
    /* Constructors */

    Vertex() : x(0), y(0), z(0) {} // default
    Vertex(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}

    // Copy constructor
    Vertex(Vertex * v, Stl_data * _data) : x(v->getx()), y(v->gety()), z(v->getz()), data(_data)  {}

    /* Getters */

    float getx() const { return x; };
    float gety() const { return y; };
    float getz() const { return z; };
    Stl_data* getdata(){ return data;};

    /* Return the list of triangle indexes */
    std::vector<int> get_connected_triangle() { return connected_triangles; }

    /* Setters */

    void setx(float _x) { x=_x;};
    void sety(float _y) { y=_y;};
    void setz(float _z) { z=_z;};

    /* Other methods */

    /* Return the type of the vertex: Simple, Complex, or Boundary */
    char vertexType(int vertex_index, float *dist);

    /* Add the index of the triangle to the list */
    void add_connected_triangle(int index) { connected_triangles.push_back(index); };

    // Return the crossproduct (*this)^v
    Vertex crossProduct(Vertex & v) { return (Vertex(y*v.getz() - z*v.gety(), z*v.getx() - x*v.getz(), x*v.gety() - y*v.getx())); }

    // Return the dot product (*this).v
    float dot(Vertex & v) { return (x*v.getx() + y*v.gety() + z*v.getz()); }

    // Invert the vertex
    void invert() { x=-x; y=-y; z=-z; };

    // Return the norm of the vertex
    float norm() { return std::sqrt(x*x + y*y + z*z); };

    // Normalize the vertex
    void normalize();

    // Return the vertex v-(*this)
    Vertex vectorTo(Vertex & v) { return (Vertex(v.getx() - x, v.gety() - y, v.getz() - z)); };

    // Return the norm of the vertex v-(*this)
    float distanceTo(Vertex & v);

    // Compute the distance between the vertex and the (line v1Edge, v2Edge)
    float distance_to_edge (Vertex & v1Edge, Vertex & v2Edge);

    /* Return the number of triangle the vertex has in common with v */
    int nbCommonTriangleWith(Vertex &v);

    /* Remove from the connected_triangles list the triangle index t
     * if it is inside  */
    void removeTriangle(int t);

    /* Decrement the vertices indexes if they are greater than i */
    void decalTriangles(int i_min);
  };

  // Surcharge de == pour les vertex
  bool operator==(const Vertex v1, const Vertex v2);

  // Surcharge de l'opérateur << pour l'affichage des informations d'un point
  std::ostream& operator<<(std::ostream& out, const stl::Vertex& p);
}
