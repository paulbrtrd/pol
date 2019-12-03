#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <algorithm>
#include "parse_stl.h"
#include "tools.h"
#include <cmath>
namespace stl {


  /* -------------------------------------*/
 /* -------------- VERTEX ---------------*/
/* -------------------------------------*/
  void Vertex::normalize() {
    float norm = std::sqrt(x*x + y*y + z*z);
    x/=norm;
    y/=norm;
    z/=norm;
  }


   /* -------------------------------------*/
  /* ------------- TRIANGLE --------------*/
 /* -------------------------------------*/

/* Constructors */
  Triangle::Triangle(int normalp, int v1p, int v2p, int v3p, Stl_data * datap){
    normal_i = normalp;
	  v1_i = v1p;
	  v2_i = v2p;
	  v3_i = v3p;
    data = datap;

  }

  Triangle::Triangle(Triangle * t) {
    normal_i = t->getnormal_i();
    v1_i = t->getv1_i();
    v2_i = t->getv2_i();
    v3_i = t->getv3_i();
  }

/* Getters */
  Vertex Triangle::getv1() const
  {
    return (data->getvertices())->at(v1_i);
  }

  Vertex Triangle::getv2() const
  {
    return (data->getvertices())->at(v2_i);
  }
  Vertex Triangle::getv3() const
  {
    return (data->getvertices())->at(v3_i);
  }
  Vertex Triangle::getnormal() const
  {
    return (data->getnormals())->at(normal_i);
  }

  int Triangle::getv_i(int i) const {
    switch(i) {
      case 1:
        return v1_i;
      case 2:
        return v2_i;
      case 3:
        return v3_i;
      default:
        std::cout << "Error: in getv(): return normal" << std::endl;
        return normal_i;
    }
  }
  Vertex Triangle::getv(int i) const {
    switch(i) {
      case 1:
        return this->getv1();
      case 2:
        return this->getv2();
      case 3:
        return this->getv3();
      default:
        std::cout << "Error: in getv(): return normal" << std::endl;
        return this->getnormal();
    }
  }

  Vertex Triangle::getOrientation() {
    Vertex A = this->getv1();
    Vertex B = this->getv2();
    Vertex C = this->getv3();

    Vertex AB = A.vectorTo(B);
    Vertex AC = A.vectorTo(C);

    Vertex orientation = AB.crossProduct(AC);
    orientation.normalize();
    return orientation;
  }
  void Triangle::getLastVertices(int first_point, int * A, int * B) {
    if (v1_i == first_point) {
      *A = v2_i;
      *B = v3_i;
      return;
    }
    if (v2_i == first_point) {
      *A = v1_i;
      *B = v3_i;
      return;
    }
    if (v3_i == first_point) {
      *A = v1_i;
      *B = v2_i;
      return;
    }
    *A = -1;
    *B = -1;
  }


   /* -------------------------------------*/
  /* ------------- STL_DATA --------------*/
 /* -------------------------------------*/

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
      this->addTriangle(Triangle(i_normal, i_v1, i_v2, i_v3, this));

      char dummy[2];
      stl_file.read(dummy, 2);
    }
  }

/* Getters */

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

      std::cout << "Normale " << i+1 << " ajouté" << std::endl;

      Vertex v1 = t.getv1();
      vertex_to_buf(v_bin, v1);
      new_file.write(v_bin, 12);

      std::cout << "Vertex 1 de  " << i+1 << " ajouté" << std::endl;

      Vertex v2 = t.getv2();
      vertex_to_buf(v_bin, v2);
      new_file.write(v_bin, 12);

      std::cout << "Vertex 2 de  " << i+1 << " ajouté" << std::endl;

      Vertex v3 = t.getv3();
      vertex_to_buf(v_bin, v3);
      new_file.write(v_bin, 12);

      std::cout << "Vertex 3 de  " << i+1 << " ajouté" << std::endl;

      // Décalage de 2 octets entre chaque triangle (voir parse_stl)
      new_file.write(dummy, 2);
      std::cout << "Triangle " << i+1 << " ajouté" << std::endl;
      i++;

    }
    new_file.close();
  }

  Stl_data * Stl_data::reducted_mesh() {

    // List of triangles to keep
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
      }
    }

    // Création du nouveau Stl_data
    Stl_data *result = new Stl_data;
    result->setname(name);
    int current_triangle = 0;

    // Pour chaque triangle que l'on veut conserver
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
      result->addTriangle(Triangle(i_normal, i_v1, i_v2, i_v3, result));
    }

    return result;

  }

}
