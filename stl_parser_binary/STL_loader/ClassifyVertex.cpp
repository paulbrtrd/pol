
#include "ClassifyVertex.h"
#include <algorithm>
#include <iostream>


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



//// a completer















  return dist;

}
