#include "car.h"
#include <GL/glut.h>

static float carPos = -50.0f;

CarSystem::CarSystem() {}
void CarSystem::init() { carPos = -50.0f; }
void CarSystem::update(float dt) { carPos += 20.0f * dt; if (carPos > 50.0f) carPos = -50.0f; }

void CarSystem::render() {
    glPushMatrix();
    glTranslatef(carPos, 0.5f, 20.0f);
    glScalef(2.0f, 0.5f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}
