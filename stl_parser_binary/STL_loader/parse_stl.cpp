#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "parse_stl.h"
#include "tools.h"

namespace stl {
  /* ------------- TRIANGLE -------------*/
  Triangle::Triangle(Vertex * normalp, Vertex * v1p, Vertex * v2p, Vertex * v3p){
      normal = normalp;
	  v1 = v1p;
	  v2 = v2p;
	  v3 = v3p;bool simpleVertex(Vertex v);

	  v1->add_connected_triangle(this);
	  v2->add_connected_triangle(this);
	  v3->add_connected_triangle(this);
  }

  Vertex Triangle::getv(int i) const {
    switch(i) {
      case 1:
        return *v1;
      case 2:
        return *v2;
      case 3:
        return *v3;
      default:
        std::cout << "Error: in getv(): return normal" << std::endl;
        return *normal;
    }

  }

  /* ------------- STL_DATA -------------*/

  Stl_data::Stl_data(const std::string& stl_path) {
    std::ifstream stl_file(stl_path.c_str(), std::ios::in | std::ios::binary);
    if (!stl_file) {
      std::cout << "ERROR: COULD NOT READ FILE" << std::endl;
      assert(false);
    }

    char header_info[80] = "";
    char n_triangles[4];
    stl_file.read(header_info, 80);
    stl_file.read(n_triangles, 4);
    std::string h(header_info);
    //Stl_data info(h);
    this->name = h;
    unsigned int* r = (unsigned int*) n_triangles;
    unsigned int num_triangles = *r;
    for (unsigned int i = 0; i < num_triangles; i++) {
      auto normal = parse_vertex(stl_file);
      auto v1 = parse_vertex(stl_file);
      auto v2 = parse_vertex(stl_file);
      auto v3 = parse_vertex(stl_file);

	  Vertex * ptr_normal = this->get_or_add_vertex(normal);
	  Vertex * ptr_v1 = this->get_or_add_vertex(v1);
	  Vertex * ptr_v2 = this->get_or_add_vertex(v2);
	  Vertex * ptr_v3 = this->get_or_add_vertex(v3);

      //info.triangles.push_back(triangle(normal, v1, v2, v3));
    this->addTriangle(Triangle(ptr_normal, ptr_v1, ptr_v2, ptr_v3));// add both the triangle and this triangle to the connected triangles vector of each vertex
    this->addVertices(Vertex (ptr_v1->getx(),ptr_v1->gety(),ptr_v1->getz()));
    this->addVertices(Vertex (ptr_v2->getx(),ptr_v2->gety(),ptr_v2->getz()));
    this->addVertices(Vertex (ptr_v3->getx(),ptr_v3->gety(),ptr_v3->getz()));

    char dummy[2];
    stl_file.read(dummy, 2);
    }
  }

  Vertex * Stl_data::get_or_add_vertex(Vertex & v) {
	  for (Vertex & existing_v: vertices) {
		  if (v == existing_v) {
			  return &existing_v;
		  }
	  }
	  vertices.push_back(v);
	  return & vertices.back();
  }

  void Stl_data::addVertices(Vertex  vert) {
    for (Vertex & existing_v: vertices)
    {
      if (vert == existing_v){return;}
      vertices.push_back(vert);
    }
  };

  void Stl_data::create_stl() {
    // Open the file
    std::ofstream new_file("created_file.stl",std::ofstream::binary);

    // Extract the list of triangles
    std::vector<stl::Triangle> triangles = this->gettriangles();

    /* Les données à écrire doivent être des const char
    --> Conversion du name et de n_triangle en const char */
    const char * name = this->getname().c_str();
    unsigned int n_triangles = triangles.size();
    const char * n = (const char *) &n_triangles;

    // 80 premier octets: le nom
    new_file.write( name , 80);

    // 4 octets suivant: le nombre de triangles
    new_file.write(n, 4);

    // buffer contenant les 3 coordonnées du point courant
    char v_bin[12];

    // 2 octets de séparation entre 2 polygones
    char dummy[2];

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

      // Décalage de 2 octets entre chaque triangle (voir parse_stl)
      new_file.write(dummy, 2);

    }
    new_file.close();
  }



}
