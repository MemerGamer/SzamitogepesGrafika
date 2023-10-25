#include "glut.h"
#include <cmath>

static GLfloat spin = 0.0;
GLdouble posX, posY, posZ;
double l1 = 30.0; // Length of the first arm
double l2 = 20.0; // Length of the second arm
double minAngle =  M_PI; // Minimum angle of the second arm, in radians, can be changed to any value between 0 and 180 degrees

// Helper function to calculate joint angles
void calculateIKAngles(double targetX, double targetY, double& angle1, double& angle2) {
    double x = targetX;
    double y = targetY;

    // Calculate cosTheta1, clamped to the range [-1, 1]
    double cosTheta1 = std::max(-1.0, std::min(1.0, (x * x + y * y - l1 * l1 - l2 * l2) / (2 * l1 * l2)));

    angle1 = atan2(y, x) - atan2(l2 * sin(acos(cosTheta1)), l1 + l2 * cos(acos(cosTheta1)));


    angle2 = acos(cosTheta1);
    // Minimum angle
     if (angle2 > minAngle) {
        angle2 = minAngle;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear color is black
    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Calculate joint angles based on the mouse position
    double angle1, angle2;
    calculateIKAngles(posX, posY, angle1, angle2);

    // Draw the first joint (circle shape) at the fixed point
    glColor3f(1.0, 1.0, 1.0);
    float radius = 2;
    glutWireSphere(radius, 20, 20);

    // Draw the first arm
    glPushMatrix();
    glRotatef(angle1 * 180.0 / M_PI, 0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);  // Starting point at the fixed joint
    glVertex2f(l1, 0.0);   // End point of the first arm
    glEnd();
    glTranslatef(l1, 0.0, 0.0);

    // Draw the second joint (circle shape) at the end of the first arm
    glutWireSphere(radius, 20, 20);

    glRotatef(angle2 * 180.0 / M_PI, 0.0, 0.0, 1.0);

    // Draw the second arm
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);  // Starting point at the end of the first arm
    glVertex2f(l2, 0.0);   // End point of the second arm
    glEnd();

    // Position the end effector (circle shape) at the end of the second arm
    glTranslatef(l2, 0.0, 0.0);
    glutWireSphere(radius, 20, 20);

    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Exit on pressing the Escape key
}

void spinDisplay() {
    spin += 0.5;
    if (spin > 360)
        spin -= 360;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
        if (state == GLUT_UP)
            glutIdleFunc(nullptr);
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-50, 50, -50 * (GLfloat) h / (GLfloat) w, 50 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
    else
        glOrtho(-50 * (GLfloat) w / (GLfloat) h, 50 * (GLfloat) w / (GLfloat) h, -50, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GoTo(double x, double y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Inverse Kinematics");
    glutPassiveMotionFunc(MouseMove);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
