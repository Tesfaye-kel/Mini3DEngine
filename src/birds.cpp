#include "birds.h"
#include <GL/glut.h>
#include <cmath>

Birds::Birds(float r, float g, float b, int count, float radius)
    : m_count(count), m_radius(radius), m_angle(0.0f)
{
    m_color[0] = r; m_color[1] = g; m_color[2] = b;
}

void Birds::init() { m_angle = 0.0f; }

void Birds::update(float dt) {
    m_angle += 20.0f * dt; // deg/sec
    if (m_angle > 360.0f) m_angle -= 360.0f;
}

void Birds::render() {
    // simple flock: small spheres moving in a circle with slight vertical bob
    glPushMatrix();
    for (int i = 0; i < m_count; ++i) {
        float a = (m_angle + i * (360.0f / m_count)) * 3.14159265f / 180.0f;
        float x = cosf(a) * m_radius;
        float y = 12.0f + sinf(a * 2.0f) * 2.0f;
        float z = sinf(a) * m_radius;
        glPushMatrix();
        glTranslatef(x,y,z);
        glColor3f(m_color[0], m_color[1], m_color[2]);
        glutSolidSphere(0.2,6,6);
        glPopMatrix();
    }
    glPopMatrix();
}

void Birds::setColor(float r, float g, float b) {
    m_color[0] = r; m_color[1] = g; m_color[2] = b;
}
