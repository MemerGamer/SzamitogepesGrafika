#include "glut.h"

/**
 * gluProject - vetites
 * openGL koordinata-rendszerbol windows ablak koordinata-rendszerbe
 * **/

static GLfloat spin = 0.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // a törlõszín a fekete
    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);             //töröljük a képernyõt

    glPushMatrix();


    glPopMatrix();                                         // puffer-csere
    glutSwapBuffers();
    glFlush();                                             // rajzolj!
}

void keyboard(unsigned char key, int x, int y)              // billentûkezelés
{
//    switch (key) {
//        case 27:                                                // ha escape-et nyomtam
//            exit(0);                                           // lépjen ki a programból
//            break;
//    }
    if (key == 27) exit(0); // ha escape-et nyomtam, lépjen ki a programból
}

void spinDisplay() {
    spin = spin + 0.5;
    if (spin > 360)
        spin = spin - 360;
    glutPostRedisplay();                                     // újrarajzolás
}

void mouse(int button, int state, int x, int y) {
//    switch (button) {
//        case GLUT_LEFT_BUTTON:
//            if (state == GLUT_DOWN)
//                glutIdleFunc(spinDisplay);
//            if (state == GLUT_UP)
//                glutIdleFunc(NULL);
//            break;
//        default:
//            break;
//    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) glutIdleFunc(spinDisplay);
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // az ablak kétszeresen pufferelt,és RGB módú
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
