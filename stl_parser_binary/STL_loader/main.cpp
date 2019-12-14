#include <cassert>
#include <iostream>

#include "Structures/stl_data.h"
#include "Structures/vertex.h"
#include "Structures/triangle.h"

//#include "tools.h"
#include "ClassifyVertex.h"


#include <cassert>
#include <iostream>

#include "opengl_display.h"

int main(int argc, char* argv[]) {
  std::string stl_file_name = "moto.stl";

  // Si le nom du fichier est donné en argument, on utilise celui donné
  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }

  bool open_gl_initiated = false;

  // Extraction des données depuis le fichier stl
  stl::Stl_data * info_ptr = new stl::Stl_data(stl_file_name);
  stl::Stl_data * new_info_ptr;
  char choice = 'a';

  std::vector<stl::Triangle> triangles = *(info_ptr->gettriangles());
  std::vector<stl::Vertex> * vertices = info_ptr->getvertices();
  std::vector<stl::Vertex> * normals = info_ptr->getnormals();
  // Boucle UI
  while(true) {
    std::cout << "Que voulez-vous faire?\n" <<
                  "1. Afficher les informations du fichier\n" <<
                  "2. Afficher la liste des vertices\n" <<
                  "3. Afficher la liste des normales\n" <<
                  "4. Afficher la liste des triangles du fichier\n" <<
                  "5. Afficher le fichier chargé avec openGL\n" <<
                  "6. Créer un fichier stl à partir des infos chargées\n" <<
                  "7. Appliquer l'algorithme\n" <<
                  "0. Quitter" << std::endl;
    std::cin >> choice;
    int c=0;
    int i=0;
    int nb_c = 0;
    int nb_s = 0;
    int nb_b = 0;
    int nb_simple_candidate = 0;
    int nb_boundary_candidate;
    switch(choice)
    {
      case '1':
        std::cout << "Header = " << info_ptr->getname() << std::endl;
        std::cout << "Nombre de triangles = " << triangles.size() << std::endl;
        std::cout << "Nombre de vertices = " << vertices->size() << std::endl;
        nb_simple_candidate = 0;
        for (int j=0; j<vertices->size(); j++) {
          stl::Vertex v = vertices->at(j);
          float dist = 0;
          char vertex_type = v.vertexType(j, &dist);
          if (vertex_type == 's' && dist < 0.1) {
            nb_simple_candidate++;
          }
        }
        std::cout << "Nombre de vertices candidats = " << nb_simple_candidate << std::endl;
        break;
      case '2':
        std::cout << "\nListe des vertices:\n";
        nb_c = 0;
        nb_s = 0;
        nb_b = 0;
        nb_simple_candidate = 0;
        nb_boundary_candidate = 0;


        for (int j=0; j<vertices->size(); j++) {
          stl::Vertex v = vertices->at(j);
          float dist = 0;
          char vertex_type = v.vertexType(j, &dist);
          std::cout << v << " (" << vertex_type << ")" << std::endl;
          switch (vertex_type) {
            case 's':

              if (dist < 0.1) {
                nb_simple_candidate++;
              }
              nb_s++;
              break;
            case 'c':
              nb_c++;
              break;
            case 'b':
              if (dist < 0.1) {
                nb_boundary_candidate++;
              }
              nb_b++;
              break;
            default:
              break;
          }
        }
        std::cout << "B: " << nb_b << "\tC: " << nb_c << "\tS: " << nb_s << " simple Candidates : " << nb_simple_candidate << "  boundary Candidates : " << nb_boundary_candidate<< std::endl;

        break;
      case '3':
        std::cout << "\nListe des normales:\n";
        for (stl::Vertex n : *normals) {
          std::cout << n << std::endl;

        }
        break;
      case '4':
        std::cout << "\nListe des triangles:\n";

        for (stl::Triangle t : triangles) {
          std::cout << t << std::endl;
          c = (t.getv1_i());
          std::cout << c << std::endl;
        }

        break;
      case '5':
        // Init openGL
        if (!open_gl_initiated) {
          init_opengl(argc, argv);
          open_gl_initiated = true;
        }
        opengl_display(info_ptr);
        break;
      case '6':
        info_ptr->create_stl();
        std::cout << "File created: created_file.stl" << std::endl;
        break;
      case '7':
        info_ptr->delete_one_vertex();
        triangles = *(info_ptr->gettriangles());
        vertices = info_ptr->getvertices();
        normals = info_ptr->getnormals();
        break;

      case '0':
        return 0;
      default:
        std::cout << "Cette commande n'est pas disponible" << std::endl;
    }

  }

}
