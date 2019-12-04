#pragma once
#include "Structures/vertex.h"


//classify vertex
bool simpleVertex(stl::Vertex v);
bool complexVertex(stl::Vertex v);
bool boundaryVertex(stl::Vertex v);
bool interiorEdgeVertex(stl::Vertex v);
bool cornerVertex(stl::Vertex v);

//criteria for approving the deletion of the vertex or not
std::vector <int> equation_plane(stl::Vertex v1, stl::Vertex v2,stl::Vertex v3);
float distance_to_plane(stl::Vertex v1, stl::Vertex v2,stl::Vertex v3,stl::Vertex v);
