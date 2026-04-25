#include <GL/glut.h>
#include <GL/glu.h>

void display() {
    // Clear the buffers (clear color was set during init)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up modelview and camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // place camera a bit along +Z so we can see objects at the origin
    gluLookAt(0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    // Draw a colored triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // GLU usage: perspective setup
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    // Set clear color (dark blue) once during initialization
    glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("My OpenGL (GLUT + GLU)");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}