#include <GL/freeglut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <string>
#include <iostream>

GLuint cubeTextures[6]; // Array to store texture IDs
GLuint sphereTexture;
GLfloat cubeVertices[][12] = {
        {-1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f},  // Front face
        {-1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f},  // Back face
        {1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f},  // Right face
        {-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f},  // Left face
        {-1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f},  // Top face
        {-1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f}  // Bottom face
};

float rotationX = 0.0f;
float rotationY = 0.0f;
int lastMouseX = 0;
int lastMouseY = 0;
bool isMousePressed = false;

bool focusOnCube = true;

void loadTexture(const char *filename, GLuint *textureID) {
    *textureID = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
    );

    if (*textureID == 0) {
        // Handle the error, e.g., print an error message or exit the program.
        std::cerr << "Error loading texture: " << filename << std::endl;
    }
}

void keyboard(unsigned char key, int x, int y) {
    // Toggle between focusing on the cube and the sphere when the 'c' key is pressed
    if (key == 'c' || key == 'C') {
        focusOnCube = !focusOnCube;
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Load textures with repeating images
//    loadTexture("shreksy.bmp", &cubeTextures[0]);  // Front
    loadTexture("IvyTexture.bmp", &cubeTextures[0]);  // Front
    loadTexture("IvyTexture.bmp", &cubeTextures[1]);  // Back
    loadTexture("WoodGrain.bmp", &cubeTextures[2]);  // Top
    loadTexture("WoodGrain.bmp", &cubeTextures[3]);  // Bottom
    loadTexture("LightningTexture.bmp", &cubeTextures[4]);  // Right
    loadTexture("RedLeavesTexture.bmp", &cubeTextures[5]);  // Left

    // Load sphere texture
    loadTexture("earth.bmp", &sphereTexture);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Register keyboard callback function
    glutKeyboardFunc(keyboard);
}

void drawTexturedCube() {
    // Define texture indices for each face
    GLuint faceTextures[] = {0, 1, 2, 3, 4, 5};

    for (int i = 0; i < 6; ++i) {
        glBindTexture(GL_TEXTURE_2D, cubeTextures[faceTextures[i]]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(cubeVertices[i][0], cubeVertices[i][1], cubeVertices[i][2]);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(cubeVertices[i][3], cubeVertices[i][4], cubeVertices[i][5]);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(cubeVertices[i][6], cubeVertices[i][7], cubeVertices[i][8]);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(cubeVertices[i][9], cubeVertices[i][10], cubeVertices[i][11]);
        glEnd();
    }
}

void drawTexturedSphere() {
    glBindTexture(GL_TEXTURE_2D, sphereTexture);
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, 1.0, 50, 50);
    gluDeleteQuadric(quadric);
}


void drawText(const std::string& text, float x, float y) {
    // Save the current state of texturing
    GLboolean isTextureEnabled = glIsEnabled(GL_TEXTURE_2D);

    // Disable texturing for rendering text
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    double matrix[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0.0f, 800.0f, 0.0f, 600.0f, -5.0f, 5.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x, y);
    for (char i : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, i);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);

    // Restore the previous state of texturing
    if (isTextureEnabled) {
        glEnable(GL_TEXTURE_2D);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    if (focusOnCube) {
        // Draw the textured cube
        drawTexturedCube();
    } else {


        // Draw the textured sphere
        drawTexturedSphere();
    }
    // Display message in the left corner
    std::string message = "Press 'c' to switch between cube and sphere";
    drawText(message, 10.0f, 10.0f);
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
        rotationX += (float(y) - float(lastMouseY)) * 0.1f;
        rotationY += (float(x) - float(lastMouseX)) * 0.1f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Textured Cube and Sphere");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
