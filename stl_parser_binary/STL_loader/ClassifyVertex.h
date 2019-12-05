#pragma once
#include "Structures/vertex.h"


//classify vertex
bool complexVertex(stl::Vertex v);
bool boundaryVertex(stl::Vertex v);
bool interiorEdgeVertex(stl::Vertex v);
bool cornerVertex(stl::Vertex v);



std::vector <int> list_connected_vertices(stl::Vertex v);
float distance_vertices (stl::Vertex v1, stl::Vertex v2);

bool vertex_criterea(stl::Vertex v, float dist_critere);
