#include "house.h"
#include <GL/glut.h>

House::House() {}
void House::init() {}
void House::update(float dt) {}

void House::render() {
    // simple modern house block
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(4.0f, 1.5f, 6.0f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glutSolidCube(1.0);
    glPopMatrix();

    // glass front (as a quad)
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, -3.01f);
    glColor4f(0.2f, 0.5f, 0.7f, 0.6f);
    glBegin(GL_QUADS);
        glVertex3f(-1.8f, -0.5f, 0.0f);
        glVertex3f(1.8f, -0.5f, 0.0f);
        glVertex3f(1.8f, 0.9f, 0.0f);
        glVertex3f(-1.8f, 0.9f, 0.0f);
    glEnd();
    glPopMatrix();
}
