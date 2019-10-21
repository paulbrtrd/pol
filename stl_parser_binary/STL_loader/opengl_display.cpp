#include "opengl_display.h"
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

float step = 0.3;
float camPosX = 0;
float camPosY = 0;
float camPosZ = 2;
stl::Stl_data * ptr_mesh_to_display;


// Definition de la fonction d'affichage
GLvoid affichage(){
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
   

   //glBegin(GL_QUAD_STRIP);
   //glEnable(GL_TEXTURE_2D);

   // Extraction des triangles
   std::vector<stl::Triangle> triangles = ptr_mesh_to_display->gettriangles();
   // Dessin de chaque triangle
   stl::Vertex firstPoint = triangles.back().getv1();
   float cali_x, cali_y, cali_z;
   cali_x = firstPoint.getx() - camPosX;
   cali_y = firstPoint.gety() - camPosY;
   cali_z = firstPoint.gety();

   for (stl::Triangle t : triangles) {
      glBegin(GL_TRIANGLES);
      stl::Vertex normal = t.getnormal();
      glNormal3f(normal.getx(), normal.gety(), normal.getz());
      for(int i=1; i<=3; i++) {
         stl::Vertex v = t.getv(i);
         glVertex3f(v.getx() - cali_x, v.gety() - cali_y, v.getz() - cali_z);
      }
      glEnd();
   }

   //glEnd();
   
   // A vous de mettre en commentaire la boucle ci-dessus
   // et de mettre en place les 6 glBegin(GL_QUADS) permettant
   // de dessiner les 6 faces du cube
   
   
   

   glFlush();
   glutSwapBuffers();
}

// Definition de la fonction gerant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) {
   
   // Suivant les touches pressees, nous aurons un comportement different de l'application
   // ESCAPE ou 'q' : fermera l'application
   // 'p' : affichage du carre plein
   // 'f' : affichage du carre en fil de fer
   // 's' : affichage des sommets du carre
   switch(touche) {
      case 'p' : // carre plein
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         break;
      case 'f' : // fil de fer
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
      case 's' : // sommets du carre
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
         break;
         
         // Gestion du tampon de profondeur
      case 'd' :
         // TODO : activer le test du tampon de profondeur
         glutPostRedisplay();
         break;
      case 'D' :
         //TODO : desactiver le test du tampon de profondeur
         glutPostRedisplay();
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
         
         
      case 'q' : // quitter
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
         // On remet le delate deplacement a 0
      case GLUT_KEY_UP :
         camPosZ -= step;
         somethingChanged = true;
         break;
      case GLUT_KEY_DOWN :
         camPosZ += step;
         somethingChanged = true;
         break;

      case GLUT_KEY_RIGHT :
         camPosX += step;
         somethingChanged = true;
         break;
      case GLUT_KEY_LEFT :
         camPosX -= step;
         somethingChanged = true;
         break;
         
         break;
   }
   // Demande a GLUT de reafficher la scene
   if (somethingChanged)
      glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y){
   // Test pour voir si le bouton gauche de la souris est appuyé
   //TODO
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
   
   // Viewport
   // // TODO Essayez de modifier l'appel à glViewport
   // en changeant les parametre d'appel a la fonction mais
   // tout en obtenant le meme resultat
   glViewport(0, 0, windowW, windowH);
   
   // Mise en place de la perspective
   // TODO : peut-on changerle ratio ici pour un meilleur resultat ?
   gluPerspective(focale, 4/3.0, near, far);
   
   // Placement de la caméra
   //gluLookAt(camPosX, camPosY, camPosZ, 0, 0, 0, 0, 1, 0);
   
   // Retourne a la pile modelview
   glMatrixMode(GL_MODELVIEW);
}
void init_opengl(int argc, char *argv[])
{
   // Initialisation de GLUT
   glutInit(&argc, argv);
}

void opengl_display(stl::Stl_data * ptr_mesh)
{
   // Update the mesh reference
   ptr_mesh_to_display = ptr_mesh;
   // Initialisation de GLUT
   //glutInit(&argc, argv);
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
   glutDisplayFunc(affichage);
   glutKeyboardFunc(clavier);
   // Nouveaux callbacks
   glutMouseFunc(souris);
   glutMotionFunc(deplacementSouris);
   glutReshapeFunc(redimensionner);
   glutSpecialUpFunc(releaseSpecialKey);
   
   // Lancement de la boucle infinie GLUT
   glutMainLoop();
   
}
