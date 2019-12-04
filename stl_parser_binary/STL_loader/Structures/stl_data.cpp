#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <algorithm>
#include "tools.h"
#include "stl_data.h"
#include "triangle.h"
#include "vertex.h"

namespace stl {
  /* Constructor */
  Stl_data::Stl_data(const std::string& stl_path) {

    // Extract the file
    std::ifstream stl_file(stl_path.c_str(), std::ios::in | std::ios::binary);
    if (!stl_file) {
      std::cout << "ERROR: COULD NOT READ FILE" << std::endl;
      assert(false);
    }

    // Extract header
    char header_info[80] = "";
    stl_file.read(header_info, 80);
    std::string h(header_info);
    name = h;

    // Extract triangles
    char n_triangles[4]; // the number of triangle is encoded on 4 bytes
    stl_file.read(n_triangles, 4);
    unsigned int* r = (unsigned int*) n_triangles;
    unsigned int num_triangles = *r;

    for (unsigned int i = 0; i < num_triangles; i++) {
      std::cout << 100*i/num_triangles << "%" << std::endl;
      Vertex normal = parse_vertex(stl_file);
      Vertex v1 = parse_vertex(stl_file);
      Vertex v2 = parse_vertex(stl_file);
      Vertex v3 = parse_vertex(stl_file);

      // Create or get the index to the normal and the vertices
      int i_normal = this->get_or_add_normal(normal, i);
      int i_v1 = this->get_or_add_vertex(v1, i);
      int i_v2 = this->get_or_add_vertex(v2, i);
      int i_v3 = this->get_or_add_vertex(v3, i);

      // Add the triangle to the list
      Triangle t(i_normal, i_v1, i_v2, i_v3, this);
      this->addTriangle(t);

      char dummy[2];
      stl_file.read(dummy, 2);
    }
  }

  int Stl_data::get_or_add_vertex(Vertex & v, int current_triangle) {
    // Check if the vertex already exists
    for (int i=0; i<vertices.size(); i++){
      if (v == vertices[i]) {
        // Vertex found: add the current triangle to the connected_triangles of the vertex
        // and return the index of the vertex in the list
        vertices[i].add_connected_triangle(current_triangle);
        return i;
      }
    }

    // Vertex not found. Create a new vertex and add it in the vertices list
    Vertex * new_v = new Vertex(&v, this);
    new_v->add_connected_triangle(current_triangle);
    vertices.push_back(*new_v);
    return vertices.size() - 1;
  }

  int Stl_data::get_or_add_normal(Vertex & n, int current_triangle) {
    for (int i= 0; i<normals.size(); i++) {
      if (n == normals[i]) {
        normals[i].add_connected_triangle(current_triangle);
        return i;
      }
    }
    Vertex * new_n = new Vertex(&n, this);
    new_n->add_connected_triangle(current_triangle);
    normals.push_back(*new_n);
    return normals.size() - 1;
  }

  void Stl_data::create_stl() {
    // Open the file
    std::ofstream new_file("created_file.stl",std::ofstream::binary);

    /* Les données à écrire doivent être des const char
    --> Conversion du name et de n_triangle en const char */
    const char * name_bin = name.c_str();
    unsigned int n_triangles = triangles.size();
    const char * n = (const char *) &n_triangles;

    // 80 premier octets: le nom
    new_file.write( name_bin , 80);

    // 4 octets suivant: le nombre de triangles
    new_file.write(n, 4);

    // buffer contenant les 3 coordonnées du point courant
    char v_bin[12];

    // 2 octets de séparation entre 2 polygones
    char dummy[2];

    int i = 0;

    // Écriture des données
    for (Triangle t: triangles) {
      Vertex normal = t.getnormal();
      vertex_to_buf(v_bin, normal);
      new_file.write(v_bin, 12);

      Vertex v1 = t.getv1();
      vertex_to_buf(v_bin, v1);
      new_file.write(v_bin, 12);

      Vertex v2 = t.getv2();
      vertex_to_buf(v_bin, v2);
      new_file.write(v_bin, 12);

      Vertex v3 = t.getv3();
      vertex_to_buf(v_bin, v3);
      new_file.write(v_bin, 12);

      // Décalage de 2 octets entre chaque triangle (voir le constructeur de Stl_data)
      new_file.write(dummy, 2);
      std::cout << "Triangle " << i+1 << " ajouté" << std::endl;
      i++;

    }
    new_file.close();
  }

  Stl_data * Stl_data::reducted_mesh() {

    // Création du nouveau Stl_data
    Stl_data *result = new Stl_data;
    result->setname(name);
    int current_triangle = 0;

    // List of triangles to keep (copy of the list of triangle indexes)
    std::vector<int> triangles_to_keep;
    for(int j=0; j<triangles.size();j++) {
      triangles_to_keep.push_back(j);
    }

    for(int i=0;i<vertices.size();i++) {
      // Un vertex sur 5 est supprimé
      if (i%5==0) {
        // Tous les triangles associés à ce vertex sont supprimé
        std::vector<int> triangles_to_delete = vertices.at(i).get_connected_triangle();
        for(int & t: triangles_to_delete) {
          // Chaque triangle est donc retiré de triangles_to_keep, si il y est encore
          std::vector<int>::iterator it = std::find(triangles_to_keep.begin(), triangles_to_keep.end(), t);
          if (it != triangles_to_keep.end()) {
            triangles_to_keep.erase(it);
          }
        }

        /* Retriangulation */

        // Vertex au centre du trou engendré par la suppression (vertex qui sera supprimé)
        Vertex v0 = vertices.at(i);
        // Triangle de base (choisi arbitairement)
        Triangle * t_ptr = &triangles.at(triangles_to_delete.at(0));

        // Sommets des triangles à construire (stocké sous forma d'indices)
        int A = -1;
        int B = -1;
        int C = -1;

        // Extraction des deux sommets extérieurs au cycle formé
        // par le trou que la suppression de triangles engendre
        t_ptr->getLastVertices(i, &A, &B);
        Vertex v1 = vertices.at(A);

        for (int t=1; t<triangles_to_delete.size(); t++) {
          t_ptr = &triangles.at(triangles_to_delete.at(t));
          t_ptr->getLastVertices(i, &B, &C);
          if (B != A && C != A)
          {
            // Si le triangle en cours n'est pas le triangle de base
            Vertex v2 = vertices.at(B);
            Vertex v3 = vertices.at(C);

            Vertex AB = v1.vectorTo(v2);
            Vertex AC = v1.vectorTo(v3);

            Vertex normal = AB.crossProduct(AC);
            normal.normalize();
            Vertex crossprod = AB.crossProduct(AC);
            // L'orientation du triangle est nécessaire au choix de l'ordre des
            // points A, B et C lors de la création du nouveau triangle
            Vertex triangle_orientation = t_ptr->getOrientation();

            if(triangle_orientation.dot(crossprod) < 0)
            {
              // Si le nouveau triangle ABC n'est pas orienté pareil
              // que le triangle original, on inverse B et C, et le sens de la normale.
              v2 = vertices.at(C);
              v3 = vertices.at(B);
              normal.invert();
            }

            // Ajout de ABC dans le nouveau Stl_data
            int i_normal = result->get_or_add_normal(normal, current_triangle);
            int i_v1 = result->get_or_add_vertex(v1, current_triangle);
            int i_v2 = result->get_or_add_vertex(v2, current_triangle);
            int i_v3 = result->get_or_add_vertex(v3, current_triangle);

            // Add the triangle to the list
            Triangle t(i_normal, i_v1, i_v2, i_v3, result);
            result->addTriangle(t);
            current_triangle ++;
          }
        }
      }
    }

    // Ajout des triangles qui n'ont pas été supprimés
    for (int & i:triangles_to_keep) {
      Triangle t = triangles.at(i);
      Vertex normal = t.getnormal();
      Vertex v1 = t.getv1();
      Vertex v2 = t.getv2();
      Vertex v3 = t.getv3();

      // Create or get the index to the normal and the vertices
      int i_normal = result->get_or_add_normal(normal, current_triangle);
      int i_v1 = result->get_or_add_vertex(v1, current_triangle);
      int i_v2 = result->get_or_add_vertex(v2, current_triangle);
      int i_v3 = result->get_or_add_vertex(v3, current_triangle);

      // Add the triangle to the list
      Triangle new_t(i_normal, i_v1, i_v2, i_v3, result);
      result->addTriangle(new_t);
      current_triangle ++;
    }
    return result;
  }
} // namespace stl