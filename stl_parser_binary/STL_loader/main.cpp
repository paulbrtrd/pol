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
  stl::Stl_data info(stl_file_name);
  int choice = -1;

  std::vector<stl::Triangle> triangles = *(info.gettriangles());
  std::vector<stl::Vertex> * vertices = info.getvertices();
  // Boucle UI
  while(true) {
    std::cout << "Que voulez-vous faire?\n" <<
                  "1. Afficher la liste des triangles du fichier\n" <<
                  "2. Afficher les informations du fichier\n" <<
                  "3. Afficher le fichier chargé avec openGL\n" <<
                  "4. Créer un fichier stl à partir des infos chargées\n" <<
                  "5. Afficher la liste des vertices\n" <<
                  "0. Quitter" << std::endl;
    std::cin >> choice;
    int i=0;
    switch(choice) 
    {
      case 1:
        for (auto t : triangles) {
          std::cout << "(" << i << ")" << t << std::endl;
          i++;
        }
        break;
      case 2:
        std::cout << "STL HEADER = " << info.getname() << std::endl;
        std::cout << "Nombre de triangles = " << triangles.size() << std::endl;
        std::cout << "Nombre de vertices = " << vertices->size() << std::endl;
        break;
      case 3:
        // Init openGL
        if (!open_gl_initiated) {
          init_opengl(argc, argv);
          open_gl_initiated = true;
        }
        opengl_display(&info);
        break;
      case 4:
        info.create_stl();
        std::cout << "File created: created_file.stl" << std::endl;
        break;
      case 5:
        for (auto v : *vertices) {
          std::cout << v << std::endl;
        }
        break;
      case 0:
        return 0;
      default:
        std::cout << "Cette commande n'est pas disponible" << std::endl;
    }
    
  }

}

