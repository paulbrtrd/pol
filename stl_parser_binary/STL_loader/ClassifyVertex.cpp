
#include "ClassifyVertex.h"
#include <algorithm>
#include <iostream>
#include <math.h>


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
  float a= plane.at(0);
  float b= plane.at(1);
  float c= plane.at(2);
  float d= plane.at(3);
  float x= v.getx();
  float y= v.gety();
  float z= v.getz();

  if (a==0 && b==0 && c==0){
    return -1;
  }
  else {
    dist = abs( a*x + b*y + c*z +d)/sqrt(a*a + b*b + c*c);
    return dist;
  }

}




///////////////////////////////////////////////////////////////////////////////////////////////

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
  for (stl::Triangle t:connected_triang){
      for (int i=1;i<=3;i++){
        v_courant = t.getv(i);
        if (!(v_courant==v)){
            for (int j=0; j<((data->getvertices())->size()) ; j++){
              if (v_courant==((data->getvertices())->at(j))){
                vect_vertices.push_back(j);
              }
            }
        }
      }
  }

  return vect_vertices;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////



bool vertex_critirea(stl::Vertex v, float dist_critirea)
{
  std::vector<int> list_vertices_index = list_connected_vertices(v);
  stl::Stl_data * data = v.getdata();
  std::vector<stl::Vertex> * list_vertices = data->getvertices();
  std::cout << "taille :" << list_vertices ->size()<<std::endl;
  stl::Vertex a = list_vertices->at(list_vertices_index.at(0));
  std::cout<< "the first vertex of the plane : " << a <<std::endl;
  stl::Vertex b = list_vertices->at(list_vertices_index.at(1));
  std::cout<< "the second vertex of the plane : " << b <<std::endl;
  stl::Vertex c = list_vertices->at(list_vertices_index.at(2));
  std::cout<< "the third vertex of the plane : " << c <<std::endl;

  float dist = distance_to_plane (a,b,c,v);
  if (dist >=0)
  {
    if (dist < dist_critirea ){
      std::cout<<"distance of the vertex to the plane : "<< dist <<"  is little enough so that the vertex can be deleted"<<std::endl;
      return true;
    }
    else {
      std::cout<<"distance of the vertex to the plane : "<< dist << "  is big enough so that the vertex can't be deleted"<<std::endl;
      return false;
    }
  }
  else{
    std::cout<<"the plan can't be determined with the 3 vertices choosen for this application because they are collinear "<<std::endl;
    return false;
  }
}
