#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "parse_stl.h"
#include "tools.h"

namespace stl {

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
      //info.triangles.push_back(triangle(normal, v1, v2, v3));
      this->addTriangle(Triangle(normal, v1, v2, v3));
      
      char dummy[2];
      stl_file.read(dummy, 2);
    }
  }

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


