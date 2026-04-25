#include "plane.h"
#include <GL/glut.h>
#include <cmath>

static float planePos = -200.0f;

PlaneSystem::PlaneSystem() {}
void PlaneSystem::init() { planePos = -200.0f; }
void PlaneSystem::update(float dt) { planePos += 60.0f * dt; if (planePos > 200.0f) planePos = -200.0f; }

void PlaneSystem::render() {
    glPushMatrix();
    glTranslatef(planePos, 50.0f, -100.0f);
    glScalef(4.0f, 1.0f, 4.0f);
    glColor3f(0.8f,0.8f,0.8f);
    glutSolidTeapot(1.0);
    glPopMatrix();
}
