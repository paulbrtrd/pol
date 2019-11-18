
#include "ClassifyVertex.h"


bool simpleVertex(stl::Vertex v){
  std::vector <Triangle *> connected_triang = v.get_connected_triangle();
  for (Triangle & t: connected_triang){
    /*vérifier que tous les arêtes liant le
    vertex v et l'autre de triangle
    appatient exactement à deux triangles*/

    /*
    vérifier que le vertex v est entouré
    par un cercle complet d'arêtes
    */
  }
  return true;
}
