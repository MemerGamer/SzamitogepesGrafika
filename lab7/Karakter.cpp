#include <GL/freeglut.h>
#include <iostream>
#include <SOIL/SOIL.h>

// Define the window size
const int windowWidth = 800;
const int windowHeight = 600;

// Define the character's width and height
int characterWidth;
int characterHeight;

// Define the character's position
float characterX = 0;
float characterY = (windowHeight - characterHeight) / 2.0f;

// Define the character's speed
float characterSpeed = 2.0f;

// Define the texture ID
GLuint characterTexture;

// Load the character's texture from a PNG file
void loadCharacterTexture(const char* filename) {
    characterTexture = SOIL_load_OGL_texture(
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
    );

    if (characterTexture == 0) {
        std::cerr << "Error loading character texture" << std::endl;
    } else {
        glBindTexture(GL_TEXTURE_2D, characterTexture);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &characterWidth);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &characterHeight);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// Initialize OpenGL
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    loadCharacterTexture("Jumper-transparent.png");

    // Center the character vertically
    characterY = (windowHeight - characterHeight) / 2.0f;
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, characterTexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(characterX, characterY);
    glTexCoord2f(1, 0);
    glVertex2f(characterX + characterWidth, characterY);
    glTexCoord2f(1, 1);
    glVertex2f(characterX + characterWidth, characterY + characterHeight);
    glTexCoord2f(0, 1);
    glVertex2f(characterX, characterY + characterHeight);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glutSwapBuffers();
}

// Timer function
void timer(int value) {
    characterX += characterSpeed;
    if (characterX > windowWidth) {
        characterX = -characterWidth;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Character Animation");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}
