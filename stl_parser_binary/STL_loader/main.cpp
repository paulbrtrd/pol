#include <cassert>
#include <iostream>

#include "Structures/stl_data.h"
#include "Structures/vertex.h"
#include "Structures/triangle.h"

#include "opengl_display.h"

int main(int argc, char* argv[]) {
  // Fichier par défaut: un cube de 8 vertices et 12 triangles
  std::string stl_file_name = "Box1x1x1.stl";

  // Si le nom du fichier est donné en argument, on utilise celui donné
  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }

  // Extraction des données depuis le fichier stl
  stl::Stl_data * info_ptr = new stl::Stl_data(stl_file_name);
  // Extraction des informations utiles pour l'affichage
  std::vector<stl::Triangle> triangles = *(info_ptr->gettriangles());
  std::vector<stl::Vertex> vertices = *(info_ptr->getvertices());
  std::vector<stl::Vertex> normals = *(info_ptr->getnormals());

  /* Boucle UI */

  // Choix de l'utilisateur
  char choice;

  // Pour initialiser openGL une seule fois.
  bool open_gl_initiated = false;

  // Variables pour le décompte des différents types de vertices
  int nb_simple_vertices = 0;
  int nb_complex_vertices = 0;
  int nb_boundary_vertices = 0;
  int nb_simple_candidates = 0;
  int nb_boundary_candidates = 0;

  while(true) {
    std::cout << "Que voulez-vous faire?\n" <<
                  "1. Afficher les informations du fichier\n" <<
                  "2. Afficher la liste des vertices\n" <<
                  "3. Afficher la liste des normales\n" <<
                  "4. Afficher la liste des triangles du fichier\n" <<
                  "5. Afficher le fichier chargé avec openGL\n" <<
                  "6. Créer un fichier stl à partir des infos chargées\n" <<
                  "7. Supprimer 1 vertex (le meilleur candidat)\n" <<
                  "0. Quitter" << std::endl;
    std::cin >> choice;


    switch(choice)
    {
      case '1': /* Affichage des informations */
        std::cout << "Header = " << info_ptr->getname() << std::endl;
        std::cout << "Nombre de triangles = " << triangles.size() << std::endl;
        std::cout << "Nombre de vertices = " << vertices.size() << std::endl;
        nb_simple_candidates = 0;
        nb_boundary_candidates = 0;
        for (int j=0; j<vertices.size(); j++) {
          stl::Vertex v = vertices.at(j);
          float dist = 0;
          char vertex_type = v.vertexType(j, &dist);
          if ( vertex_type == 's' && dist < 0.1) {
            nb_simple_candidates++;
          }
          if ( vertex_type == 'b' && dist < 0.1) {
            nb_boundary_candidates++;
          }
        }
        std::cout << "Nombre de simple vertices candidats = " << nb_simple_candidates << std::endl;
        std::cout << "Nombre de boundary vertices candidats = " << nb_boundary_candidates << std::endl;
        break;
      case '2': /* Affichage des vertices */
        std::cout << "\nListe des vertices:\n";
        nb_complex_vertices = 0;
        nb_simple_vertices = 0;
        nb_boundary_vertices = 0;
        nb_simple_candidates = 0;
        nb_boundary_candidates = 0;


        for (int j=0; j<vertices/size(); j++) {
          stl::Vertex v = vertices.at(j);
          float dist = 0;
          char vertex_type = v.vertexType(j, &dist);
          // Affichage du vertex
          std::cout << v << " (" << vertex_type << ")" << std::endl;

          // Décompte du nombre de vertex complex/simple/boundary, candidat ou non
          switch (vertex_type) {
            case 's':
              if (dist < 0.1) {
                nb_simple_candidates++;
              }
              nb_simple_vertices++;
              break;
            case 'c':
              nb_complex_vertices++;
              break;
            case 'b':
              if (dist < 0.1) {
                nb_boundary_candidates++;
              }
              nb_boundary_vertices++;
              break;
            default:
              break;
          }
        }
        // Affichage du résultat du décompte
        std::cout << nb_boundary_vertices << "boundary vertices. "<< nb_boundary_candidates << " candidats pour être supprimés" << std::endl;
        std::cout << nb_simple_vertices << "simple vertices. "<< nb_simple_candidates << " candidats pour être supprimés" << std::endl;
        std::cout << nb_complex_vertices << "complex vertices. "<< 0 << " candidats pour être supprimés" << std::endl;
        break;
      case '3': /* Affichage de la liste des normales */
        std::cout << "\nListe des normales:\n";
        for (stl::Vertex n : normals) {
          std::cout << n << std::endl;
        }
        break;
      case '4': /* Affichage de la liste de triangles */
        std::cout << "\nListe des triangles:\n";
        for (stl::Triangle t : triangles) {
          std::cout << t << std::endl;
          c = (t.getv1_i());
          std::cout << c << std::endl;
        }
        break;
      case '5': /* Affichage de l'objet avec openGL */
        // Init openGL
        if (!open_gl_initiated) {
          init_opengl(argc, argv);
          open_gl_initiated = true;
        }
        opengl_display(info_ptr);
        break;
      case '6': /* Sauvegarde du fichier en .stl */
        info_ptr->create_stl();
        std::cout << "Fichier créé: created_file.stl" << std::endl;
        break;
      case '7': /* Application de l'algorithme pour supprimer le vertex
                 * qui correspond le plus au critère de suppression */
        info_ptr->delete_one_vertex();
        triangles = *(info_ptr->gettriangles());
        vertices = *(info_ptr->getvertices());
        normals = *(info_ptr->getnormals());
        break;

      case '0': /* Quitter l'application */
        return 0;
      default:
        std::cout << "Cette commande n'est pas disponible" << std::endl;
    }

  }

}
