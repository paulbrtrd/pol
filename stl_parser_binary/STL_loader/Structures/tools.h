/*
 * Ces trois fonctions sont des outils de  convertion des données binaire en flottants
 * et inversement
 *
 * Merci à dillonhuff pour ces 3 fonctions et la structure générale du
 * code d'extraction des données d'un fichier stl
 * Source: https://github.com/dillonhuff/stl_parser
 * La license de ces fichiers est dans le dossier.
 */
 
#pragma once
#include "vertex.h"

namespace stl{
  // Convert stream to float
  float parse_float(std::ifstream& s);

  // Convert stream to vertex
  Vertex parse_vertex(std::ifstream& s);

  // Write the buffer for the vertex v
  void vertex_to_buf(char * buf, Vertex & v);
}
