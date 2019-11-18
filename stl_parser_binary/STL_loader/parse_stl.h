#ifndef PARSE_STL_H
#define PARSE_STL_H


#include <string>
#include <vector>
#pragma once
namespace stl {

class Triangle;
class Vertex;
class Stl_data;

/* ------------- VERTEX -------------*/
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
    Vertex() : x(0), y(0), z(0) {}
    Vertex(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}
    Vertex(Vertex * v, Stl_data * _data) : x(v->getx()), y(v->gety()), z(v->getz()), data(_data)  {}

    float getx() const { return x; };
    float gety() const { return y; };
    float getz() const { return z; };
    Stl_data* getdata(){ return data;};
    /* Add the index of the triangle to the list */
	  void add_connected_triangle(int index) { connected_triangles.push_back(index); };
    /* Return the list of triangle indexes */
    std::vector<int> get_connected_triangle() { return connected_triangles; }

};

/* ------------- TRIANGLE -------------*/
  class Triangle {
  private:
    /* Indexes of the normal, v1, v2, and v3 in the vertices list */
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
    int getnormal_i() const { return normal_i; };

    Stl_data* getdata(){return data;};

    /* Return a COPY of the vertex or normal */
    Vertex getv1() const;
    Vertex getv2() const;
    Vertex getv3() const;
    Vertex getnormal() const;
    Vertex getv(int i) const;
  };

/* ------------- STL_DATA -------------*/
  // Classe qui contient toutes les données d'un fichier stl
  class Stl_data {
  private:
    /* header, description du fichier (80 octets) */
    std::string name;

    /* List of triangles extracted from the file */
    std::vector<Triangle> triangles;
    /* List of vertices extracted from the file */
    std::vector<Vertex> vertices;
    /* List of normals extracted from the file */
    std::vector<Vertex> normals;

  public:
    /* Extract triangles, vertices, normals from the file */
    Stl_data(const std::string& stl_path);
    /* Add the triangle to the triangle list */
    void addTriangle(Triangle t) { triangles.push_back(t); } ;
    /* Return the index of the vertex in the vertices list if it exists,
       Add the vertex and return its index else */
	  int get_or_add_vertex(Vertex & v, int current_triangle);
    /* Return the index of the normal in the normals list if it exists,
       Add the normal and return its index else */
    int get_or_add_normal(Vertex & n, int current_triangle);

    /* Getters on the lists of triangles, normals and vertices */
    std::vector<Triangle> * gettriangles() { return &triangles; };
    std::vector<Vertex> * getvertices() { return &vertices; };
    std::vector<Vertex> * getnormals() { return &normals; };
    /* Getter on the header */
    std::string getname() const { return name; };

    /* Create binary stl file from triangle list */
    void create_stl();
  };
}


#endif
