#include "water.h"
#include <GL/glut.h>
#include <cmath>

static float waterOffset = 0.0f;

WaterSystem::WaterSystem() {}
void WaterSystem::init() { waterOffset = 0.0f; }
void WaterSystem::update(float dt) { waterOffset += dt * 0.5f; }

void WaterSystem::render() {
    glPushMatrix();
    glTranslatef(-30.0f, 0.0f, -30.0f);
    glColor3f(0.0f, 0.3f, 0.5f);
    glBegin(GL_QUADS);
        float size = 60.0f;
        glVertex3f(-size, 0.0f, -size);
        glVertex3f(size, 0.0f, -size);
        glVertex3f(size, 0.0f, size);
        glVertex3f(-size, 0.0f, size);
    glEnd();
    glPopMatrix();
}
