#pragma once
#include "parse_stl.h"

namespace stl{
float parse_float(std::ifstream& s);

Vertex parse_vertex(std::ifstream& s);

// Write the buffer for the vertex v
void vertex_to_buf(char * buf, Vertex & v);



// Surcharge de l'opérateur << pour l'affichage des informations d'un point
std::ostream& operator<<(std::ostream& out, const stl::Vertex p);
// Surcharge de l'opérateur << pour l'affichage des informations d'un triangle
std::ostream& operator<<(std::ostream& out, const stl::Triangle& t);

// Surcharge de == pour les vertex
bool operator==(const Vertex v1, const Vertex v2);

}
