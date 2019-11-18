#pragma once

#ifdef __WINDOWS__
#include <Windows.h>
#endif

#include "parse_stl.h"



#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif




void init_opengl(int argc, char *argv[]);
void opengl_display (stl::Stl_data * ptr_mesh);

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid clavier(unsigned char touche, int x, int y);
GLvoid releaseSpecialKey(int key, int x, int y);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);
