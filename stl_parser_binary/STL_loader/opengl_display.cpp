#include "opengl_display.h"
#include "Structures/vertex.h"
#include "Structures/triangle.h"

#include <vector>
#include <iostream>

// Quelques variables globales (c'est pas bien)
GLfloat pointSize = 1.0f;

// Rotations autour de X et Y
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLint oldX = 0;
GLint oldY = 0;
float deltaX = 0;
float deltaY = 0;
GLboolean boutonClick = false;

// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float near = 0.1f;
float far = 100.0f;
// Variables used to set the center of the window
float cali_x, cali_y, cali_z;
float x_bary=0, y_bary=0, z_bary=0;

// Step for the modifications of the user
float step = 0.3;

// Camera position
float camPosX = 0;
float camPosY = 0;
float camPosZ = 2;

// Stl_data instance of the displayed mesh
stl::Stl_data * info_ptr;
// Triangles used to display the mesh
std::vector<stl::Triangle> triangles_to_display;

/* true if the user pressed a key to
* reduct the mesh (r, *, or number between 1 and 9 ) */
bool mesh_reduction_wanted=false;
// the reduction will delete reduction_force*5% of the vertices number of the mesh
int reduction_force = 1;

void init_opengl(int argc, char *argv[])
{
  // Initialisation de GLUT
  glutInit(&argc, argv);
}
// Display Callback
GLvoid display(){
  // Effacement du frame buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Suppression du Z-buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);

  // Animation du cube!
  glLoadIdentity();

  // Placement de la caméra
  gluLookAt(camPosX, camPosY, camPosZ, camPosX, camPosY, 0, 0, 1, 0);

  glRotatef(angleY,1.0f,0.0f,0.0f);
  glRotatef(angleX,0.0f,1.0f,0.0f);


  cali_x = x_bary - camPosX;
  cali_y = y_bary - camPosY;
  cali_z = z_bary;

  /* if the user chose to reduct the mesh */
  if (mesh_reduction_wanted) {
    int nb_reduction;
    mesh_reduction_wanted = false;

    /* Compute the number of vertices to delete */
    if (reduction_force != 0) {
      if (reduction_force == 10) {
        // Deletion of the maximum vertices possible
        nb_reduction = (info_ptr->getvertices())->size();
      }
      else {
        // Deletion of the reduction_force*5% of the vertices
        nb_reduction = (reduction_force * 5 * (info_ptr->getvertices())->size()) / 100;
      }
    }
    else {
      // Deletion of only 1 vertex
      nb_reduction = 1;
    }

    bool more_candidates = true;
    for(int i=0;i<nb_reduction;i++) {
      more_candidates = info_ptr->delete_one_vertex();
      std::cout << "Reduction ... (" << 100*i/nb_reduction << "%)" << std::endl;
      if (!more_candidates) {
        std::cout << "No more candidates. " << i << " vertices deleted" << std::endl;
        break;
      }
    }
    std::cout << "Reduction: " << reduction_force*5 << "% (" << nb_reduction << " vertices)"<< std::endl;
    std::cout << "Nombre de triangles = " << triangles_to_display.size() << std::endl;
    std::cout << "Nombre de vertices = " << (info_ptr->getvertices())->size() << std::endl;
    triangles_to_display = *(info_ptr->gettriangles());
  }

  /* Display the triangles */
  for (stl::Triangle t : triangles_to_display) {
    glBegin(GL_TRIANGLES);
    stl::Vertex normal = t.getnormal();
    glNormal3f(normal.getx(), normal.gety(), normal.getz());
    for(int i=1; i<=3; i++) {
      stl::Vertex v = t.getv(i);
      /* Vertex is translated of (cali_x, cali_y, cali_z) to center
      * the object in the window */
      glVertex3f(v.getx() - cali_x, v.gety() - cali_y, v.getz() - cali_z);
    }
    glEnd();
  }
  glFlush();
  glutSwapBuffers();
}

// Definition de la fonction gerant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) {

  /*
  Keyboard callback:
  ** Display modes:
  - 'p': fill the triangles
  - 'f': display lines
  - 's': display only vertices
  - '+': increase vertices size
  - '-': decrease vertices size
  ** Mesh reduction options:
  - 'r': delete one Vertex
  - '1': delete 1*5% of the vertices
  - '2': delete 2*5%=10% of the vertices
  - 'n': 0<n<10: delete n*5% of the vertices
  - '*'; delete the maximum number of vertices possible
  ** Save option:
  - 'e'/'E': Save the current mesh as stl
  ** Exit option:
  - Echap/'q': close window and exit application
  */
  switch(touche) {

    /* Display options */

    case 'p' : // carre plein
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
    case 'f' : // fil de fer
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    break;
    case 's' : // sommets du carre
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    break;
    case '+':
    // Augmenter la taille des sommets affiches
    pointSize+=1.0f;
    glPointSize(pointSize);
    break;
    case '-':
    // Augmenter la taille des sommets affiches
    pointSize-=1.0f;
    if(pointSize<= 0.0f)
    pointSize = 1.0f;
    glPointSize(pointSize);
    break;

    /* Mesh reduction */

    case 'r':
    mesh_reduction_wanted = true;
    reduction_force = 0;  // 1 vertex will be deleted
    break;
    case '1':
    mesh_reduction_wanted = true;
    reduction_force = 1;  // 5% of the vertices will be deleted
    break;
    case '2':
    mesh_reduction_wanted = true;
    reduction_force = 2;  // 10% of the vertices will be deleted
    break;
    case '3':
    mesh_reduction_wanted = true;
    reduction_force =3;  // 15% of the vertices will be deleted
    break;
    case '4':
    mesh_reduction_wanted = true;
    reduction_force = 4;  // 20% of the vertices will be deleted
    break;
    case '5':
    mesh_reduction_wanted = true;
    reduction_force = 5;  // 25% of the vertices will be deleted
    break;
    case '6':
    mesh_reduction_wanted = true;
    reduction_force = 6;  // 30% of the vertices will be deleted
    break;
    case '7':
    mesh_reduction_wanted = true;
    reduction_force = 7;  // 35% of the vertices will be deleted
    break;
    case '8':
    mesh_reduction_wanted = true;
    reduction_force = 8;  // 40% of the vertices will be deleted
    break;
    case '9':
    mesh_reduction_wanted = true;
    reduction_force = 9;  // 45% of the vertices will be deleted
    break;
    case '*':
    mesh_reduction_wanted = true;
    reduction_force = 10;  // Every candidate vertex will be deleted
    break;

    /* Save option */

    case 'e':
    case 'E':
    info_ptr->create_stl();
    std::cout << "Saved as created_stl.stl" << std::endl;
    break;

    /* Exit */

    case 'q' :
    case 27 :
    exit(0);
    break;
  }

  // Demande a GLUT de reafficher la scene
  glutPostRedisplay();
}

// Fonction de gestion du clavier (touche speciale relachee)
GLvoid releaseSpecialKey(int key, int x, int y) {
  bool somethingChanged = false;
  switch (key) {
    case GLUT_KEY_UP :  // reculer la caméra
      camPosZ -= step;
      somethingChanged = true;
      break;
    case GLUT_KEY_DOWN : // Avancer la caméra
      camPosZ += step;
      somethingChanged = true;
      break;
    default:
      break;
  }

  // Demande a GLUT de reafficher la scene
  if (somethingChanged)
    glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y){
  if (bouton == GLUT_LEFT_BUTTON) {
    if (etat == GLUT_DOWN) {
      boutonClick = true;
      oldX = x;
      oldY = y;

    }
    else if (etat == GLUT_UP && boutonClick) {
      boutonClick = false;
      deltaX = angleX;
      deltaY = angleY;
    }
  }
}

GLvoid deplacementSouris(int x, int y) {
  // si le bouton gauche est appuye et qu'on se deplace
  // alors on doit modifier les angles de rotations du cube
  // en fonction de la derniere position de la souris
  // et de sa position actuelle
  if (boutonClick) {
    angleX = deltaX + x - oldX;
    angleY = deltaY + y - oldY;
  }

  // Appeler le re-affichage de la scene OpenGL
  glutPostRedisplay();
}

// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
  // Garde les valeurs
  windowW = w;
  windowH = h;
  // eviter une division par 0
  if(windowH==0)
  windowH = 1;

  float ratio = (float)windowW / (float)windowH;
  //cout << "Ratio : " << ratio << endl;

  // Projection
  glMatrixMode(GL_PROJECTION);

  // Resetting matrix
  glLoadIdentity();
  glViewport(0, 0, windowW, windowH);

  // Mise en place de la perspective
  gluPerspective(focale, 4/3.0, near, far);

  // Retourne a la pile modelview
  glMatrixMode(GL_MODELVIEW);
}

void opengl_display(stl::Stl_data * ptr_mesh)
{
  // Update the mesh triangles to display
  info_ptr = ptr_mesh;
  triangles_to_display = *(info_ptr->gettriangles());

  std::vector<stl::Vertex> vertices = *(info_ptr->getvertices());
  // Compute barycenter of the object
  x_bary=0;
  y_bary=0;
  z_bary=0;
  for(stl::Vertex & v : vertices)
  {
    x_bary += v.getx();
    y_bary += v.gety();
    z_bary += v.getz();
  }
  x_bary/=vertices.size();
  y_bary/=vertices.size();
  z_bary/=vertices.size();

  // Choix du mode d'affichage (ici RVB)
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

  // Position initiale de la fenetre GLUT
  glutInitWindowPosition(200, 200);

  // Taille initiale de la fenetre GLUT
  glutInitWindowSize(windowW, windowH);

  // Creation de la fenetre GLUT
  glutCreateWindow("Mesh");

  // Définition de la couleur d'effacement du framebuffer
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Activation du Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Définition des fonctions de callbacks
  glutDisplayFunc(display);
  glutKeyboardFunc(clavier);
  glutMouseFunc(souris);
  glutMotionFunc(deplacementSouris);
  glutReshapeFunc(redimensionner);
  glutSpecialUpFunc(releaseSpecialKey);

  // Lancement de la boucle infinie GLUT
  glutMainLoop();

}
