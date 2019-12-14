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

    /* Triangulate the hole caused by the deletions of the vertex at the index i
          i: index of the vertex we want to delete
          triangles_to_delete_ptr: pointer to the list of triangles that will be
          delete at the deletion of the vertex*/

    void _fillHoles(int i,std::vector<Triangle> * triangles_to_delete_ptr);
    /* Delete the vertex at index i and its connected trangles
          i: index of the vertex
          triangles_to_delete_i_ptr: pointer to the list of the indexes of the connected triangles
    */
    void _deleteVertex(int i, std::vector<int> * triangles_to_delete_i_ptr);

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

    /* Delete one vertex if possile. Return false if not */
    bool delete_one_vertex();
  };
}
