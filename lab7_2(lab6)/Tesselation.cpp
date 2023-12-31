#include <GL/glut.h>

int lastX = 0;
int lastY = 0;
bool mouseDown = false;
float rotationX = 0.0;
float rotationY = 0.0;

int V[8][3] = {
        {-1, -1, 1},
        {1, -1, 1},
        {1, 1, 1},
        {-1, 1, 1},
        {-1, -1, -1},
        {1, -1, -1},
        {1, 1, -1},
        {-1, 1, -1}
};

int F[6][4] = {
        {2, 3, 0, 1},
        {2, 1, 5, 6},
        {6, 5, 4, 7},
        {7, 4, 0, 3},
        {3, 2, 6, 7},
        {0, 4, 5, 1}
};

float C[6][3] = {
        {1.0, 0.0, 0.0},
        {1.0, 1.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 1.0, 1.0},
        {0.5, 0.5, 0.5}
};

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear color is black
    glShadeModel(GL_FLAT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    glCallList(1);

    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Exit on pressing the Escape key
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-2, 2, -2 * (GLfloat) h / (GLfloat) w, 2 * (GLfloat) h / (GLfloat) w, -50.0, 50.0);
    else
        glOrtho(-2 * (GLfloat) w / (GLfloat) h, 2 * (GLfloat) w / (GLfloat) h, -2, 2, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = true;
            lastX = x;
            lastY = y;
        } else if (state == GLUT_UP) {
            mouseDown = false;
        }
    }
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        rotationX += (y - lastY);
        rotationY += (x - lastX);
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tessellation");
    init();

    glNewList(1, GL_COMPILE);
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        glColor3f(C[i][0], C[i][1], C[i][2]);
        for (int j = 0; j < 4; ++j) {
            int vertexIndex = F[i][j];
            glVertex3f(V[vertexIndex][0], V[vertexIndex][1], V[vertexIndex][2]);
        }
    }
    glEnd();
    glEndList();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}
