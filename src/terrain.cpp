#include "terrain.h"
#include <GL/glut.h>
#include <cmath>

Terrain::Terrain() {}
void Terrain::init() {}
void Terrain::update(float dt) {
    // environment animations can update terrain details
}

void Terrain::render() {
    // simple grid ground with texture coordinates
    glPushMatrix();
    glColor3f(0.2f, 0.6f, 0.2f);
    const int size = 200;
    const int step = 2;
    for (int z = -size; z < size; z += step) {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = -size; x <= size; x += step) {
            float h1 = 0.0f; // flat for now
            float h2 = 0.0f;
            glVertex3f((float)x, h1, (float)z);
            glVertex3f((float)x, h2, (float)(z+step));
        }
        glEnd();
    }
    glPopMatrix();
}
