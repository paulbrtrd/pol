#pragma once
#include "Structures/vertex.h"


//classify vertex
bool complexVertex(stl::Vertex v);
bool boundaryVertex(stl::Vertex v);
bool interiorEdgeVertex(stl::Vertex v);
bool cornerVertex(stl::Vertex v);



std::vector <int> list_connected_vertices(stl::Vertex v);
float distance_vertices (stl::Vertex v1, stl::Vertex v2);
float distance_to_edge (stl::Vertex v, stl::Vertex v1Edge, stl::Vertex v2Edge);

bool vertex_criteria(stl::Vertex v, char type, float dist_critere);
