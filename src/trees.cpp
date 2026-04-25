#include "trees.h"
#include <GL/glut.h>
#include <cmath>

Trees::Trees() {}
void Trees::init() {}
void Trees::update(float dt) {
    // sway could be implemented via shader or CPU-deformed vertices
}

void Trees::render() {
    // render many simple billboards/cones as trees
    glPushMatrix();
    for (int i = -50; i <= 50; i += 5) {
        for (int j = -50; j <= 50; j += 5) {
            if ((i*i + j*j) % 7 == 0) continue; // sparse
            glPushMatrix();
            glTranslatef(i * 1.5f, 0.0f, j * 1.5f);
            // trunk
            glColor3f(0.45f, 0.25f, 0.1f);
            glPushMatrix(); glTranslatef(0.0f, 0.8f, 0.0f); glScalef(0.3f,1.6f,0.3f); glutSolidCube(1.0f); glPopMatrix();
            // leaves (cone)
            glColor3f(0.1f, 0.5f, 0.1f);
            glPushMatrix(); glTranslatef(0.0f, 1.6f, 0.0f); glRotatef(-90,1,0,0); glutSolidCone(1.0,2.0,8,8); glPopMatrix();
            glPopMatrix();
        }
    }
    glPopMatrix();
}
