#pragma once


#include <string>
#include <vector>
#include "vertex.h"
#include "triangle.h"

namespace stl {
  class Triangle;
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
    /* Constructors */
    /* Extract triangles, vertices, normals from the file */
    Stl_data(const std::string& stl_path);
    Stl_data() {};

    /* Setters */
    void setname(std::string _name) { name = _name; } ;

    /* Getters */
    /* Getters on the lists of triangles, normals and vertices */
    std::vector<Triangle> * gettriangles() { return &triangles; };
    std::vector<Vertex> * getvertices() { return &vertices; };
    std::vector<Vertex> * getnormals() { return &normals; };
    /* Getter on the header */
    std::string getname() const { return name; };

    /* Add the triangle to the triangle list */
    void addTriangle(Triangle & t) { triangles.push_back(t); } ;
    /* Return the index of the vertex in the vertices list if it exists,
    Add the vertex and return its index else */
    int get_or_add_vertex(Vertex & v, int current_triangle);
    /* Return the index of the normal in the normals list if it exists,
    Add the normal and return its index else */
    int get_or_add_normal(Vertex & n, int current_triangle);

    /* Create binary stl file from triangle list */
    void create_stl();

    /* Return a Stl_data with reducted mesh */
    Stl_data * reducted_mesh();
  };
}
