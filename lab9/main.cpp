#include <GL/freeglut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

GLuint textures[6]; // Array to store texture IDs
GLfloat cubeVertices[][12] = {
        {-1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f},  // Front face
        {-1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  -1.0f, 1.0f, -1.0f},  // Back face
        {1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 1.0f},  // Right face
        {-1.0f, -1.0f, -1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, -1.0f},  // Left face
        {-1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, -1.0f,  -1.0f, 1.0f, -1.0f},  // Top face
        {-1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f}  // Bottom face
};

float rotationX = 0.0f;
float rotationY = 0.0f;
int lastMouseX = 0;
int lastMouseY = 0;
bool isMousePressed = false;

void loadTexture(const char *filename, int index) {
    textures[index] = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
    );
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Load textures with repeating images
    loadTexture("IvyTexture.bmp", 0);  // Front
//    loadTexture("shreksy.bmp", 0);  // Front
    loadTexture("IvyTexture.bmp", 1);  // Back
    loadTexture("WoodGrain.bmp", 2);  // Top
    loadTexture("WoodGrain.bmp", 3);  // Bottom
    loadTexture("LightningTexture.bmp", 4);  // Right
    loadTexture("RedLeavesTexture.bmp", 5);  // Left

    // Enable texturing
    glEnable(GL_TEXTURE_2D);
}

void drawTexturedCube() {
    // Define texture indices for each face
    GLuint faceTextures[] = {0, 1, 2, 3, 4, 5};

    for (int i = 0; i < 6; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures[faceTextures[i]]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(cubeVertices[i][0], cubeVertices[i][1], cubeVertices[i][2]);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(cubeVertices[i][3], cubeVertices[i][4], cubeVertices[i][5]);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(cubeVertices[i][6], cubeVertices[i][7], cubeVertices[i][8]);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(cubeVertices[i][9], cubeVertices[i][10], cubeVertices[i][11]);
        glEnd();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    // Draw the textured cube
    drawTexturedCube();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) w / (float) h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMousePressed = true;
            lastMouseX = x;
            lastMouseY = y;
        } else if (state == GLUT_UP) {
            isMousePressed = false;
        }
    }
}

void motion(int x, int y) {
    if (isMousePressed) {
        rotationX += (y - lastMouseY) * 0.1f;
        rotationY += (x - lastMouseX) * 0.1f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Textured Cube");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
