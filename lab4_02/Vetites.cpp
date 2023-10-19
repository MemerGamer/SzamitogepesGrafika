#include "glut.h"

/**
 * gluProject - vetites
 * openGL koordinata-rendszerbol windows ablak koordinata-rendszerbe
 * **/

static GLfloat spin = 0.0;

bool animate = false;
float szog = 0.0;
float elojel = 1.0;

void Timer(int value){
    szog += 0.5 * elojel;
    if(szog > 30) elojel = -elojel;
    if(szog < -30) elojel = -elojel;
    if(animate) glutTimerFunc(30, Timer, 0);
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_F1){
        animate = !animate;
        if(animate) glutTimerFunc(30, Timer, 0);
    }
    glutPostRedisplay();
    glutPostRedisplay();
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // a törlõszín a fekete
    glShadeModel(GL_FLAT);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);             //töröljük a képernyõt
    glPushMatrix();

    // Apply rotation to the entire pendulum
    glRotatef(szog, 1, 0, 0);

    // Draw the pendulum rod
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 10.0, 0.0);
    glVertex3f(0.0, -20.0, 0.0);
    glEnd();

    // Draw the pendulum bob
    glTranslatef(0.0, -20.0, 0.0);  // Move to the bob's position
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(5.0, 20, 20);  // Draw a red sphere as the bob

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

int main(int argc, char **argv) {
    glutInit(&argc, argv);                       // inicializáljuk a glut-ot
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // az ablak kétszeresen pufferelt,és RGB módú
    glutInitWindowSize(700, 600);                // az ablak 700x600-as
    glutInitWindowPosition(100, 100);            // az ablak bal felsõ sarkank koordinátája
    glutCreateWindow("Vetites");                  // neve Vetites
    init();                                      // inicializálás
    glutDisplayFunc(display);                    // a képernyõ események kezelése
    glutKeyboardFunc(keyboard);                  // billentyûzet események kezelése
    glutReshapeFunc(reshape);                      // újrarajzolás nagyításkor, kicsinyítéskor
    glutMouseFunc(mouse);                          // egérkezelés
    glutMainLoop();                              // belépés az esemény hurokba...
    return 0;
}
