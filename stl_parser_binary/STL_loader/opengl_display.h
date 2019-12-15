/* Code inspiré du TP2 de IMAGRV */

#pragma once

#ifdef __WINDOWS__
#include <Windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include "Structures/stl_data.h"

// Initiation of glut
void init_opengl(int argc, char *argv[]);

// Window creation and definition of the callbacks
void opengl_display (stl::Stl_data * ptr_mesh);

/* Callbacks */
GLvoid display();
GLvoid clavier(unsigned char touche, int x, int y);
GLvoid releaseSpecialKey(int key, int x, int y);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);
