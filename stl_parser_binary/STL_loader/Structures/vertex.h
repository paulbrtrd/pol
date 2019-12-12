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
    Vertex() : x(0), y(0), z(0) {}
    Vertex(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}
    Vertex(Vertex * v, Stl_data * _data) : x(v->getx()), y(v->gety()), z(v->getz()), data(_data)  {}

    /* Getters */
    float getx() const { return x; };
    float gety() const { return y; };
    float getz() const { return z; };
    void setx(float _x) { x=_x;};
    void sety(float _y) { y=_y;};
    void setz(float _z) { z=_z;};
    Stl_data* getdata(){ return data;};
    /* Return the list of triangle indexes */
    std::vector<int> get_connected_triangle() { return connected_triangles; }
    /* Return the type of the vertex: Simple, Complex, Boundary, Interior, Corner (e) */
    char vertexType(int vertex_index, float *dist);

    /* Setters */
    /* Add the index of the triangle to the list */
    void add_connected_triangle(int index) { connected_triangles.push_back(index); };

    /* Tools */
    Vertex crossProduct(Vertex & v) { return (Vertex(y*v.getz() - z*v.gety(), z*v.getx() - x*v.getz(), x*v.gety() - y*v.getx())); }
    float dot(Vertex & v) { return (x*v.getx() + y*v.gety() + z*v.getz()); }
    void invert() { x=-x; y=-y; z=-z; };
    float norm() { return std::sqrt(x*x + y*y + z*z); };
    void normalize();
    Vertex vectorTo(Vertex & v) { return (Vertex(v.getx() - x, v.gety() - y, v.getz() - z)); };
    float distanceTo(Vertex & v);
    /* Return the number of triangle the vertex has in common with v */
    int nbCommonTriangleWith(Vertex &v);
  };

  // Surcharge de == pour les vertex
  bool operator==(const Vertex v1, const Vertex v2);

  // Surcharge de l'opérateur << pour l'affichage des informations d'un point
  std::ostream& operator<<(std::ostream& out, const stl::Vertex& p);
}
