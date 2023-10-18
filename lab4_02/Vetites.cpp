#include "glut.h"

/**
 * gluProject - vetites
 * openGL koordinata-rendszerbol windows ablak koordinata-rendszerbe
 * **/

static GLfloat spin = 0.0;
GLdouble posX, posY, posZ;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // a törlõszín a fekete
    glShadeModel(GL_FLAT);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);             //töröljük a képernyõt
    glPushMatrix();

    // Rajzoljunk ki a képernyõre az egér pozíciója alapján
    float radius = 5;
    glTranslatef(posX, posY, posZ);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(radius, 20, 20);

    //

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
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) glutIdleFunc(spinDisplay);
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

void GoTo(double x, double y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview); // lekérjük a modelview mátrixot
    glGetDoublev(GL_PROJECTION_MATRIX, projection); // lekérjük a projection mátrixot
    glGetIntegerv(GL_VIEWPORT, viewport); // lekérjük a viewport-ot
    winX = (float) x;
    winY = (float) viewport[3] - (float) y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

}

void MouseMove(int x, int y) {
    GoTo(x, y);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);                       // inicializáljuk a glut-ot
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // az ablak kétszeresen pufferelt,és RGB módú
    glutInitWindowSize(700, 600);                // az ablak 700x600-as
    glutInitWindowPosition(100, 100);            // az ablak bal felsõ sarkank koordinátája
    glutCreateWindow("Vetites");                  // neve Vetites
    glutPassiveMotionFunc(MouseMove);
    init();                                      // inicializálás
    glutDisplayFunc(display);                    // a képernyõ események kezelése
    glutKeyboardFunc(keyboard);                  // billentyûzet események kezelése
    glutReshapeFunc(reshape);                      // újrarajzolás nagyításkor, kicsinyítéskor
    glutMouseFunc(mouse);                          // egérkezelés
    glutMainLoop();                              // belépés az esemény hurokba...
    return 0;
}
