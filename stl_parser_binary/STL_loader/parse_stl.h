#ifndef PARSE_STL_H
#define PARSE_STL_H


#include <string>
#include <vector>
#pragma once
namespace stl {

class Triangle;

/* ------------- VERTEX -------------*/
class Vertex {
  private:
    float x;
    float y;
    float z;
	std::vector <Triangle *> connected_triangles;


  public:
    Vertex() : x(0), y(0), z(0) {}
    Vertex(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}

    float getx() const { return x; };
    float gety() const { return y; };
    float getz() const { return z; };
	  void add_connected_triangle(Triangle * ptr_t) { connected_triangles.push_back(ptr_t); };
    std::vector <Triangle *> get_connected_triangle() {return connected_triangles; }

};

/* ------------- TRIANGLE -------------*/
  class Triangle {
  private:
    Vertex * normal;
    Vertex * v1;
    Vertex * v2;
    Vertex * v3;

  public:
    Triangle(Vertex * normalp, Vertex * v1p, Vertex * v2p, Vertex * v3p);

    Vertex getv1() const { return *v1; };
    Vertex getv2() const { return *v2; };
    Vertex getv3() const { return *v3; };
    Vertex getv(int i) const;
    Vertex getnormal() const { return *normal; };
  };

/* ------------- STL_DATA -------------*/
  // Classe qui contient toutes les données d'un fichier stl
  class Stl_data {
  private:
    // header, description du fichier (80 octets)
    std::string name;
    // Liste des triangles contenus dans le fichier
    std::vector<Triangle> triangles;
	   std::vector<Vertex> vertices;

  public:
    // Create Stl_data object containing all stl file data
    Stl_data(const std::string& stl_path);
    // Add the triangle to the triangle list
    void addTriangle(Triangle t) { triangles.push_back(t); } ;
    
	  Vertex * get_or_add_vertex(Vertex & v);
    std::vector<Triangle> * gettriangles() { return &triangles; };
    std::string getname() const { return name; };

    // Create binary stl file from triangle list
    void create_stl();
  };
}


#endif
