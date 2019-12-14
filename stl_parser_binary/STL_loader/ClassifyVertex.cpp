
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

float distance_to_edge (stl::Vertex v, stl::Vertex v1Edge, stl::Vertex v2Edge){
    stl::Vertex vect_directeur = v1Edge.vectorTo(v2Edge);
    stl::Vertex vect_v_v1Edge = v1Edge.vectorTo(v);
    stl::Vertex vect_cross_prod = vect_directeur.crossProduct(vect_v_v1Edge);
    float norm_vect_directeur = vect_directeur.norm();
    float norm_vect_cross_prod = vect_cross_prod.norm();
    return norm_vect_cross_prod/norm_vect_directeur;
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

bool vertex_criteria(stl::Vertex v, char type, float dist_critere){
  float d;
  std::vector<int> index_connected_vertices;
  index_connected_vertices = list_connected_vertices (v);
  stl::Vertex average_vertex(0,0,0);
  stl::Stl_data * data = v.getdata();
  std::vector<stl::Vertex>  list_vertices = *(data->getvertices());

  int M = index_connected_vertices.size();

  if (type == 's'){
      for ( int i : index_connected_vertices){
        average_vertex.setx( average_vertex.getx() + ((list_vertices.at(i)).getx())/M );
        average_vertex.sety( average_vertex.gety() + ((list_vertices.at(i)).gety())/M );
        average_vertex.setz( average_vertex.getz() + ((list_vertices.at(i)).getz())/M );
      }
      d= distance_vertices(average_vertex,v);

<<<<<<< HEAD
      std::cout<< " distance : "<< d <<std::endl;

      if (d<dist_critere){
        return true;
      }
      else{
        return false;
      }
=======
  if (d<dist_critere){
    return true;
>>>>>>> 3da89f0bdaf3bcfe0adf20e4b933b014cd65d85c
  }
  if (type =='b'){
      int nb_common_triangles;
      std::vector<stl::Vertex> bounds;
      for ( stl::Vertex & v_cour : list_vertices){
          nb_common_triangles = v.nbCommonTriangleWith(v_cour);
          if (nb_common_triangles==1){
              bounds.push_back(v_cour);
          }
      }
      d = distance_to_edge(v,bounds.at(0),bounds.at(1));

      std::cout << " edge vertex 1 : "<<bounds.at(0)<<std::endl;
      std::cout << " edge vertex 2 : "<<bounds.at(1)<<std::endl;

      std::cout<< " distance : "<< d <<std::endl;

      if (d<dist_critere){
        return true;
      }
      else{
        return false;
      }
  }
  return false;


}




////////////////////////////////
