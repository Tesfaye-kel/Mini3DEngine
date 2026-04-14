#include <GL/glut.h>
#include <GL/glu.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set clear color (dark blue)
    glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

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