#include "lighting.h"
#include <GL/glut.h>
#include <cmath>
using std::sin;
using std::cos;

static float sunAngle = 45.0f; // degrees

LightSystem::LightSystem() {}
void LightSystem::init() { sunAngle = 45.0f; }
void LightSystem::update(float dt) { sunAngle += 2.0f * dt; if (sunAngle > 360.0f) sunAngle -= 360.0f; }

void LightSystem::apply() {
    // set directional light based on sunAngle
    float rad = sunAngle * 3.14159265f / 180.0f;
    float lx = (float)cos(rad);
    float ly = (float)sin(rad);
    float ldir[4] = { lx, ly, 0.3f, 0.0f };
    float ambient[4] = { 0.2f, 0.2f, 0.25f, 1.0f };
    float diffuse[4] = { 0.9f, 0.8f, 0.7f, 1.0f };
    float specular[4] = { 1.0f,1.0f,1.0f,1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, ldir);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}
