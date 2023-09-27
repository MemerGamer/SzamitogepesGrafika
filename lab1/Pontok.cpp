/*
   Rajzoljunk: 
      -egy piros pontot a (10, 15), 
      -egy zöld pontot az (50, 10) és
      -egy kék pontot a (-30, -10) koordinátákra!

   A színtér forogjon!

   (Az ablak legyen 700*600-as méretû.)
*/


#include <stdlib.h>
#include "glut.h"


static GLfloat spin = 0.0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // a törlõszín a fekete
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);             //töröljük a képernyõt
    glPushMatrix();
    glEnable(GL_POINT_SMOOTH);
    glRotatef(spin, 0.0, 0.0, 1.0);
    glPointSize(15);
    glBegin(GL_POINTS);                                    // pontokat fogunk specifikálni
    glColor3f(1.0, 0.0, 0.0);                         // piros szín
    glVertex2i(10, 15);                               // egy pont a (10, 15) koordinátába
    glColor3f(0.0, 1.0, 0.0);                         // zöld szín
    glVertex2i(50, 10);                               // még egy pont
    glColor3f(0.0, 0.0, 1.0);                         // kék szín
    glVertex2i(-30, -10);                             // és még egy pont
    glEnd();

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glRotatef(spin * 3, 0.0, 0.0, 1.0);
    glVertex2i(10, 1);
    glVertex2i(9, 14);
    glVertex2i(-5, -5);
    glEnd();

    glPopMatrix();                                         // puffer-csere
    glutSwapBuffers();
    glFlush();                                             // rajzolj!
}

void keyboard(unsigned char key, int x, int y)              // billentûkezelés
{
    switch (key) {
        case 27:                                                // ha escape-et nyomtam
            exit(0);                                           // lépjen ki a programból
            break;
    }
}

void spinDisplay(void) {
    spin = spin + 0.5;
    if (spin > 360)
        spin = spin - 360;
    glutPostRedisplay();                                     // újrarajzolás
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay);
            if (state == GLUT_UP)
                glutIdleFunc(nullptr);
            break;
        default:
            break;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-50, 50, -50 * (GLfloat) h / (GLfloat) w,
                50 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
    else
        glOrtho(-50 * (GLfloat) w / (GLfloat) h,
                50 * (GLfloat) w / (GLfloat) h, -50, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);                       // inicializáljuk a glut-ot
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // az ablak kétszeresen pufferelt,és RGB módú
    glutInitWindowSize(700, 600);                // az ablak 700x600-as
    glutInitWindowPosition(100, 100);            // az ablak bal felsõ sarkank koordinátája
    glutCreateWindow("Pontok");                  // neve Pontok
    init();                                      // inicializálás
    glutDisplayFunc(display);                    // a képernyõ események kezelése
    glutKeyboardFunc(keyboard);                  // billentyûzet események kezelése
    glutReshapeFunc(reshape);                      // újrarajzolás nagyításkor, kicsinyítéskor
    glutMouseFunc(mouse);                          // egérkezelés
    glutMainLoop();                              // belépés az esemény hurokba...
    return 0;
}
