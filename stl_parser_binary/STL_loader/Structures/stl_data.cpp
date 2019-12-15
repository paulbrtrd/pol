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

      // Create or get the index of the normal and the vertices
      int i_normal = this->get_or_add_normal(normal, i);
      int i_v1 = this->get_or_add_vertex(v1, i);
      int i_v2 = this->get_or_add_vertex(v2, i);
      int i_v3 = this->get_or_add_vertex(v3, i);

      // Add the triangle to the list
      Triangle t(i_normal, i_v1, i_v2, i_v3, this);
      this->addTriangle(t);

      // Triangles are seperated by 2 bytes
      char dummy[2];
      stl_file.read(dummy, 2);
    }
  }

  int Stl_data::get_or_add_vertex(Vertex & v, int current_triangle) {
    // Check if the vertex already exists
    for (int i=0; i<vertices.size(); i++){
      if (v == vertices.at(i)) {
        // Vertex found: add the current triangle to the connected_triangles of the vertex
        // and return the index of the vertex in the list
        vertices.at(i).add_connected_triangle(current_triangle);
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
    // Same process as get_or_add_vertex, but on the normals
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
    int nb_triangles = triangles.size();
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
      std::cout << "Triangle " << i+1 << "/" << nb_triangles << " ajouté" << std::endl;
      i++;

    }

    // Fermeture du fichier
    new_file.close();
  }

  void Stl_data::_deleteVertex(int i,std::vector<int> * triangles_to_delete_i_ptr) {

    // Remove the triangles from the connected_triangle list of each vertex
    for(int & t: *triangles_to_delete_i_ptr) {
      for (Vertex & v:vertices) {
        v.removeTriangle(t);
      }
    }

    // Delete the triangles from the triangle list
    int offset = 0; // Each time a triangle is deleted, triangle with index
                    // greater than the deleted triangle lower its index
    int index;
    for(int & t: *triangles_to_delete_i_ptr) {

      /* Position of the triangle in the list */
      index = t - offset;

      /* Remove the triangle from the list */
      triangles.erase(triangles.begin() + index);

      /* The triangle at the position index is removed
      --> every position greater than index decrement */
      for (Vertex & v:vertices) {
        v.decalTriangles(index);
      }

      /* Update the offset */
      offset++;
    }

    //Once the triangles deleted, delete the vertex
    vertices.erase(vertices.begin() + i);
    for(Triangle & t: triangles) {
      t.decalVertices(i);
    }
  }

  void Stl_data::_fillHoles(int i,std::vector<Triangle> * triangles_to_delete_ptr) {

    // Indice du premier triangle qui est ajouté
    int current_triangle = triangles.size();

    // Vertex au centre du trou engendré par la suppression (vertex qui sera supprimé)
    Vertex v0 = vertices.at(i);

    // Triangle de base (choisi arbitairement)
    Triangle * t_ptr = &triangles_to_delete_ptr->at(0);

    int nb_triangle_added = 0;

    // Sommets des triangles à construire (stocké sous forma d'indices)
    int A = -1;
    int B = -1;
    int C = -1;

    // Extraction des deux sommets extérieurs au cycle formé
    // par le trou que la suppression de premier triangles engendre
    t_ptr->getLastVertices(i, &A, &B);
    // v1 = sommet commun à tous les triangles ajoutés
    Vertex v1 = vertices.at(A);

    for (int t=1; t<triangles_to_delete_ptr->size(); t++) {
      t_ptr = &triangles_to_delete_ptr->at(t);
      t_ptr->getLastVertices(i, &B, &C);
      if (B != A && C != A)   // Si le triangle en cours n'est pas le triangle de base
      {
        // Choix des deux derniers sommets du triangle que nous ajoutons
        Vertex v2 = vertices.at(B);
        Vertex v3 = vertices.at(C);

        Vertex AB = v1.vectorTo(v2);
        Vertex AC = v1.vectorTo(v3);

        // Calcul de l'orientation du triangle que nous voulons ajouter
        Vertex normal = AB.crossProduct(AC);
        normal.normalize();
        // Extraction de l'orientation du triangle initial (qui sera supprimé)
        Vertex triangle_orientation = t_ptr->getOrientation();

        if(triangle_orientation.dot(normal) < 0) // Si les deux orientation ne sont pas dans le même sens
        {
          // On inverse B et C et le sens de la normale
          v2 = vertices.at(C);
          v3 = vertices.at(B);
          normal.invert();
        }

        // Ajout de ABC dans le nouveau Stl_data
        int i_normal = get_or_add_normal(normal, current_triangle + nb_triangle_added);
        int i_v1 = get_or_add_vertex(v1, current_triangle + nb_triangle_added);
        int i_v2 = get_or_add_vertex(v2, current_triangle + nb_triangle_added);
        int i_v3 = get_or_add_vertex(v3, current_triangle + nb_triangle_added);

        // Add the triangle to the list
        Triangle t(i_normal, i_v1, i_v2, i_v3, this);
        addTriangle(t);
        nb_triangle_added ++;
      }
    }
  }

  bool Stl_data::delete_one_vertex()
  {
    /* Recherche du meilleur candidat pour la suppression */
    int best_candidate_simple = -1;
    float best_distance_simple = 0.1;
    int best_candidate_boundary = -1;
    float best_distance_boundary = 0.1;

    // Parcours des vertices
    for(int i=0; i< vertices.size();i++) {
      float dist;
      char vertex_type = vertices.at(i).vertexType(i, &dist);
      // Si le vertex est simple et vérifie le critère de distance, il est candidat
      // Le meilleur candidat est celui avec la distance la plus faible
      if ( (vertex_type=='s') && (dist < best_distance_simple) ) {
        best_candidate_simple = i;
        best_distance_simple = dist;
        if (dist == 0) {
          break;
        }
      }
      // Si le vertex est boundary et vérifie le critère de distance, il est candidat
      // Le meilleur candidat est celui avec la distance la plus faible
      else if ( (vertex_type=='b') && (dist < best_distance_boundary) ) {
        best_candidate_boundary = i;
        best_distance_boundary = dist;
        if (dist == 0) {
          break;
        }
      }
    }

    int best_candidate = -1;
    float best_distance = 0;
    if (best_candidate_simple != -1) {  // On privilégie le candidat simple
      best_candidate = best_candidate_simple;
      std::cout << "Deleting simple vertex (distance: " << best_distance_simple << ")" << std::endl;
    }
    else if (best_candidate_boundary != -1){
      best_candidate = best_candidate_boundary;
      std::cout << "Deleting boundary vertex (distance: " << best_distance_boundary << ")" << std::endl;
    }

    /* Suppression du vertex candidat */

    if (best_candidate != -1)
    {
      // Tous les triangles associés à ce vertex sont supprimé
      std::vector<int> triangles_to_delete_i = vertices.at(best_candidate).get_connected_triangle();
      std::sort(triangles_to_delete_i.begin(), triangles_to_delete_i.end());
      std::vector<Triangle> triangles_to_delete;
      for(int & j: triangles_to_delete_i) {
        triangles_to_delete.push_back(triangles.at(j));
      }

      /* Retriangulation */
      _fillHoles(best_candidate, &triangles_to_delete);
      /* Suppression du vertex */
      _deleteVertex(best_candidate, &triangles_to_delete_i);
      return true;
    }
    return false;
  }
} // namespace stl
