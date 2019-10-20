#ifndef PARSE_STL_H
#define PARSE_STL_H

#include <string>
#include <vector>

namespace stl {

/* ------------- VERTEX -------------*/
  class Vertex {
  private:
    float x;
    float y;
    float z;

  public:
    Vertex() : x(0), y(0), z(0) {}
    Vertex(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}

    float getx() const { return x; };
    float gety() const { return y; };
    float getz() const { return z; };
  };

/* ------------- TRIANGLE -------------*/
  class Triangle {
  private:
    Vertex normal;
    Vertex v1;
    Vertex v2;
    Vertex v3;

  public:
    Triangle(Vertex normalp, Vertex v1p, Vertex v2p, Vertex v3p) :
      normal(normalp), v1(v1p), v2(v2p), v3(v3p) {} ;

    Vertex getv1() const { return v1; };
    Vertex getv2() const { return v2; };
    Vertex getv3() const { return v3; };
    Vertex getv(int i) const;
    Vertex getnormal() const { return normal; };
  };

/* ------------- STL_DATA -------------*/
  // Classe qui contient toutes les données d'un fichier stl
  class Stl_data {
  private:
    // header, description du fichier (80 octets)
    std::string name;
    // Liste des triangles contenus dans le fichier
    std::vector<Triangle> triangles;

  public:
    // Create Stl_data object containing all stl file data
    Stl_data(const std::string& stl_path);
    // Add the triangle to the triangle list
    void addTriangle(Triangle t) { triangles.push_back(t); } ;

    std::vector<Triangle> gettriangles() const{ return triangles; };
    std::string getname() const { return name; };

    // Create binary stl file from triangle list
    void create_stl();
  };  
}

#endif
