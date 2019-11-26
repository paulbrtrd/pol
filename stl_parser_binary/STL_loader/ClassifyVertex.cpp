
#include "ClassifyVertex.h"
#include <algorithm>
#include <iostream>


/////////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////////////////



std::vector <int> equation_plane(stl::Vertex v1, stl::Vertex v2,stl::Vertex v3)
{

  float a1= v2.getx() - v1.getx();
  float b1= v2.gety() - v1.gety();
  float c1= v2.getz() - v1.getz();
  float a2= v3.getx() - v1.getx();
  float b2= v3.gety() - v1.gety();
  float c2= v3.getz() - v1.getz();
  float a= b1*c2 - b2*c1;
  float b= a2*c1 - a1*c2;
  float c= a1*b2 - b1*a2;
  float d=( - a*v1.getx() - b*v1.gety() - c*v1.getz());
  std::vector <int> plane;
  plane.push_back(a);
  plane.push_back(b);
  plane.push_back(c);
  plane.push_back(d);
  return plane;

}



////////////////////////////////////////////////////////////////////////////////////////


float distance_to_plane(stl::Vertex v1, stl::Vertex v2,stl::Vertex v3,stl::Vertex v)
{
  float dist;
  std::vector<int> plane;
  plane = equation_plane(v1, v2, v3);
  float 


//// a completer















  return dist;

}
