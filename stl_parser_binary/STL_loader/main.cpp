#include <cassert>
#include <iostream>

#include "parse_stl.h"
#include "tools.h"
#include "opengl_display.h"
#include "ClassifyVertex.h"


#include <cassert>
#include <iostream>

#include "parse_stl.h"
#include "tools.h"
#include "opengl_display.h"

int main(int argc, char* argv[]) {
  std::string stl_file_name = "./Box1x1x1.stl";

  // Si le nom du fichier est donné en argument, on utilise celui donné
  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }

  bool open_gl_initiated = false;

  // Extraction des données depuis le fichier stl
  stl::Stl_data info(stl_file_name);
  char choice = 'a';

  std::vector<stl::Triangle> triangles = *(info.gettriangles());
  std::vector<stl::Vertex> * vertices = info.getvertices();
  std::vector<stl::Vertex> * normals = info.getnormals();
  // Boucle UI
  while(true) {
    std::cout << "Que voulez-vous faire?\n" <<
                  "1. Afficher les informations du fichier\n" <<
                  "2. Afficher la liste des vertices\n" <<
                  "3. Afficher la liste des normales\n" <<
                  "4. Afficher la liste des triangles du fichier\n" <<
                  "5. Afficher le fichier chargé avec openGL\n" <<
                  "6. Créer un fichier stl à partir des infos chargées\n" <<
                  "0. Quitter" << std::endl;
    std::cin >> choice;
    int c=0;
    switch(choice)
    {
      case '1':
        std::cout << "Header = " << info.getname() << std::endl;
        std::cout << "Nombre de triangles = " << triangles.size() << std::endl;
        std::cout << "Nombre de vertices = " << vertices->size() << std::endl;
        break;
      case '2':
        std::cout << "\nListe des vertices:\n";
        for (stl::Vertex v : *vertices) {
          if (simpleVertex(v)){
            std::cout<< "this vertex is simple "<<std::endl;
          }
          std::cout << v << std::endl;

        }
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
          std::cout<<c<<std::endl;
        }
        break;
      case '5':
        // Init openGL
        if (!open_gl_initiated) {
          init_opengl(argc, argv);
          open_gl_initiated = true;
        }
        opengl_display(&info);
        break;
      case '6':
        info.create_stl();
        std::cout << "File created: created_file.stl" << std::endl;
        break;
      case '0':
        return 0;
      default:
        std::cout << "Cette commande n'est pas disponible" << std::endl;
    }

  }

}
