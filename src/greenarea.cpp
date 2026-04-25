#include "greenarea.h"
#include <GL/glut.h>

GreenArea::GreenArea() {}
void GreenArea::init() {}
void GreenArea::update(float dt) {}

void GreenArea::render() {
    // simple lawns and flower patches near house
    glPushMatrix();
    glTranslatef(8.0f, 0.01f, 5.0f);
    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-6.0f, 0.0f, -6.0f);
        glVertex3f(6.0f, 0.0f, -6.0f);
        glVertex3f(6.0f, 0.0f, 6.0f);
        glVertex3f(-6.0f, 0.0f, 6.0f);
    glEnd();

    // small flower patches
    for (int i = 0; i < 10; ++i) {
        glPushMatrix();
        float fx = (float)((i*37) % 10) - 5.0f; // deterministic pseudo-random
        float fz = (float)((i*73) % 10) - 5.0f;
        glTranslatef(fx, 0.01f, fz);
        glColor3f(1.0f, 0.5f, 0.6f);
        glutSolidSphere(0.2,6,6);
        glPopMatrix();
    }

    glPopMatrix();
}
