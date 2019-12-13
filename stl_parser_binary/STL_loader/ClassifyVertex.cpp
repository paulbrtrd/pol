
#include "ClassifyVertex.h"
#include <algorithm>
#include <iostream>
#include <math.h>

float distance_vertices (stl::Vertex v1, stl::Vertex v2){
  float x1=v1.getx();
  float y1=v1.gety();
  float z1=v1.getz();
  float x2=v2.getx();
  float y2=v2.gety();
  float z2=v2.getz();
  float d;
  d= sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
  return d;
}

std::vector <int> list_connected_vertices(stl::Vertex v)
{
  stl::Stl_data * data = v.getdata();
  std::vector<int> vect_vertices;
  std::vector <int> index_connected_triang = v.get_connected_triangle();
  std::vector<stl::Triangle> connected_triang;
  stl::Vertex v_courant ;

 // create connected_triangles vector
  for (int & i: index_connected_triang){
    stl::Triangle t((data->gettriangles())->at(i));
    connected_triang.push_back(t);

  }
  // create the list of indexes of the connected vertices
  int k=0;
  int l;
  for (stl::Triangle t:connected_triang){
      for (int i=1;i<=3;i++){
        v_courant = t.getv(i);
        if (!(v_courant==v)){
            for (int j=0; j<((data->getvertices())->size()) ; j++){
              if (v_courant==((data->getvertices())->at(j)) ) {
                l=0;
                while( l<vect_vertices.size() && j!= vect_vertices.at(l) ) {
                  l++;
                }
                if (l==vect_vertices.size()){
                    vect_vertices.push_back(j);
                    k++;
                }

              }
            }
        }
      }
  }

  return vect_vertices;

}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool vertex_criterea(stl::Vertex v, float dist_critere){
  float d;
  std::vector<int> index_connected_vertices;
  index_connected_vertices = list_connected_vertices (v);
  stl::Vertex average_vertex(0,0,0);
  stl::Stl_data * data = v.getdata();
  std::vector<stl::Vertex> * list_vertices = data->getvertices();

  int M = index_connected_vertices.size();

  for ( int i : index_connected_vertices){
    average_vertex.setx( average_vertex.getx() + ((list_vertices->at(i)).getx())/M );
    average_vertex.sety( average_vertex.gety() + ((list_vertices->at(i)).gety())/M );
    average_vertex.setz( average_vertex.getz() + ((list_vertices->at(i)).getz())/M );
  }
  d= distance_vertices(average_vertex,v);

  if (d<dist_critere){
    return true;
  }
  else{
    return false;
  }

}
