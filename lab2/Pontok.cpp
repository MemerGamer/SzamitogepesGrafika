/**
<h1> Definíciók: </h1>
- Eltolás: glTranslatef(a, b, c);
    x' = x + a
    y' = y + b
    z' = z + c
- Skálázás: glScalef(a, b, c);
    x' = a * x
    y' = b * y
    z' = c * z
- a, b, c > 1: nagyítás
- 0 < a, b, c < 1: kicsinyítés
- a, b, c < 0: tükrözés
- a =/= b =/= c: torzítás

- Forgatás: glRotatef(szög, x, y, z);
    szög: fokban megadott szög 0 és 360 között
    x' = x * cos(szög) - y * sin(szög)
    y' = x * sin(szög) + y * cos(szög)
    z' = z

A transzformációkat a rendszer mindig az origó körül forgatja el.

Lépések:
1. origó eltolása a forgatási középpontba
2. forgatás - glRotatef(45, 0, 0, 1);
3. origó visszatolása a kiinduló helyére


<h1> Feladat: </h2>
- rajzoljunk ki 20 db negyzetet
- 1 negyzet, kovetkezo kicsinyites, forgatas 45 fokkal
    - szineket is valtoztassuk
    - gl_quads
- használjuk a glRotatef(), scalef(), translatef() függvényeket
**/

#include "glut.h"


static GLfloat spin = 0.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);         // a törlõszín a fekete
    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);             //töröljük a képernyõt

    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);

    // Kezdeti értékek
    float size = 30.0;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    int n = 20;
    n = 12; // 12 db negyzetet rajzolunk ki

    // Ki kell rajzolnunk 20 db negyzetet egymástól eltérõ szín árnyalatokkal, kicsinyítve, forgatva
    for (int i = 0; i < n; ++i) {
        glColor3f(r, g, b);

        // Negyzet kirajzolása
        glBegin(GL_QUADS);
            glVertex2f(-size, -size);
            glVertex2f(-size, size);
            glVertex2f(size, size);
            glVertex2f(size, -size);
        glEnd();


        // Forgatás, eltolás, kicsinyítés
        glRotatef(45.0, 0.0, 0.0, 1.0);
        glScalef(0.85, 0.85, 0.0);
        glTranslatef(10.0, 10.0, 0.0);


        // Kicsinyítés és színváltoztatás
        size *= 0.99;
        r += 0.02;
        g += 0.06;
        b += 0.095;
    }


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
