#include <GL/freeglut.h>
#include <cmath>

GLfloat angle = 0.0; // Animation angle for lights
GLfloat cameraAngleX = 0.0;
GLfloat cameraAngleY = 0.0;
GLfloat cameraDistance = 4.0;

int lastMouseX, lastMouseY;
bool mouseRotate = false;

// Function to draw a cylinder
void drawCylinder(GLfloat bottom_radius,GLfloat top_radius, GLfloat height, GLint slices) {
    // Draw the cylinder using OpenGL functions
    GLUquadricObj *quadric = gluNewQuadric();
    gluCylinder(quadric, bottom_radius, top_radius, height, slices, 1);
    gluDeleteQuadric(quadric);

    glRotatef(-90.0, 1.0, 0.0, 0.0);s

}

// Function to draw the Christmas tree
void drawChristmasTree() {
    // Draw chrismas tree using the drawCylinder function
    // the log is a cylinder with radius 0.2 and height 1.0
    // the leaves are a cone with radius 1.0 and height 2.0
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0); // Position the tree
    glColor3f(0.5, 0.35, 0.05); // Brown color for the log
    drawCylinder(0.2,0.2, 1.0, 20); // Draw the log
    glTranslatef(0.0, 1.0, 0.0); // Position the leaves
    glColor3f(0.0, 0.5, 0.0); // Green color for the leaves
    drawCylinder(1.0,0.0, 2.0, 20); // Draw the leaves

    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glPopMatrix();
}

//void drawChristmasLights() {
//    glPushMatrix();
//    glTranslatef(0.0, 1.5, 0.0); // Position the lights at the top of the tree
//    glColor3f(1.0, 0.0, 0.0); // Red color for lights
//
//    // Draw lights in a spiral pattern
//    glBegin(GL_POINTS);
//    for (GLfloat i = 0; i < 360; i += 10) {
//        GLfloat x = sin(i * 3.14159 / 180.0);
//        GLfloat y = cos(i * 3.14159 / 180.0);
//        glVertex3f(x, y, 0.0);
//    }
//    glEnd();
//
//    glPopMatrix();
//}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(cameraDistance * sin(cameraAngleY) * cos(cameraAngleX),
              cameraDistance * cos(cameraAngleY),
              cameraDistance * sin(cameraAngleY) * sin(cameraAngleX),
              0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 0.0, 5.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    drawChristmasTree();
//    drawChristmasLights();

    glutSwapBuffers();
}

// Mouse callback for button presses
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
        mouseRotate = true;
    }
    else {
        mouseRotate = false;
    }
}

// Mouse callback for motion
void motion(int x, int y) {
    if (mouseRotate) {
        cameraAngleX += (x - lastMouseX) * 0.01;
        cameraAngleY += (y - lastMouseY) * 0.01;

        if (cameraAngleY > 1.5) cameraAngleY = 1.5;
        if (cameraAngleY < -1.5) cameraAngleY = -1.5;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

// Initialize OpenGL settings
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Enable mouse input
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
}

// Resize callback
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Animation function
void update(int value) {
    angle += 1.0; // Increment the angle for lights animation
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Christmas Tree");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glutTimerFunc(25, update, 0); // Set up animation timer
    glutMainLoop();
    return 0;
}
