
#include "ClassifyVertex.h"
#include <algorithm>
#include <iostream>
bool simpleVertex(stl::Vertex v){
  std::vector <int> index_connected_triang = v.get_connected_triangle();
  stl::Stl_data * data = v.getdata();
  std::vector<stl::Triangle> connected_triang;
  std::vector<stl::Vertex> vertices_connected_triang;
  int mycount;

// create connected_triangles vector
  for (int & i: index_connected_triang){
    stl::Triangle t((data->gettriangles())->at(i));
    connected_triang.push_back(t);

  }
// create vertices_connected_triangles vector
  for (stl::Triangle t:connected_triang){
      for (int i=1;i<=3;i++){
        stl::Vertex v_courant = t.getv(i);
        if (!(v_courant==v)){
            vertices_connected_triang.push_back(v_courant);
        }
      }
  }

/* check if the vertices connected to the vertex v giving in argument
   are linked only to 2 connected triangles*/
  for (stl::Vertex  vert : vertices_connected_triang){
    mycount=count(vertices_connected_triang.begin(),vertices_connected_triang.end(),vert);

    if (mycount !=2){
      return false;
    }
  }
  return true;
}
