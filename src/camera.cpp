#include "camera.h"
#include <cmath>
#include <cstdio>

Camera::Camera()
    : m_pos{0.0f, 2.0f, 10.0f}, m_yaw(180.0f), m_pitch(0.0f), m_speed(8.0f),
      m_keyW(false), m_keyA(false), m_keyS(false), m_keyD(false), m_lastMouseX(0), m_lastMouseY(0), m_firstMouse(true)
{
}

void Camera::setViewport(int w, int h) {
    // store viewport size if needed
}

void Camera::applyView() {
    float yawRad = m_yaw * 3.14159265f / 180.0f;
    float pitchRad = m_pitch * 3.14159265f / 180.0f;

    float dirX = -sinf(yawRad) * cosf(pitchRad);
    float dirY = sinf(pitchRad);
    float dirZ = -cosf(yawRad) * cosf(pitchRad);

    gluLookAt(m_pos[0], m_pos[1], m_pos[2],
              m_pos[0] + dirX, m_pos[1] + dirY, m_pos[2] + dirZ,
              0.0f, 1.0f, 0.0f);
}

void Camera::update(float dt) {
    float yawRad = m_yaw * 3.14159265f / 180.0f;
    float forwardX = -sinf(yawRad);
    float forwardZ = -cosf(yawRad);
    float rightX = cosf(yawRad);
    float rightZ = -sinf(yawRad);

    float moveX = 0.0f, moveZ = 0.0f;
    if (m_keyW) { moveX += forwardX; moveZ += forwardZ; }
    if (m_keyS) { moveX -= forwardX; moveZ -= forwardZ; }
    if (m_keyA) { moveX -= rightX;   moveZ -= rightZ; }
    if (m_keyD) { moveX += rightX;   moveZ += rightZ; }

    float len = sqrtf(moveX*moveX + moveZ*moveZ);
    if (len > 0.0001f) {
        moveX /= len; moveZ /= len;
        m_pos[0] += moveX * m_speed * dt;
        m_pos[2] += moveZ * m_speed * dt;
    }
}

void Camera::onKeyDown(unsigned char key) {
    switch (key) {
        case 'w': case 'W': m_keyW = true; break;
        case 's': case 'S': m_keyS = true; break;
        case 'a': case 'A': m_keyA = true; break;
        case 'd': case 'D': m_keyD = true; break;
        case 27: /* ESC */ exit(0); break;
    }
}
void Camera::onKeyUp(unsigned char key) {
    switch (key) {
        case 'w': case 'W': m_keyW = false; break;
        case 's': case 'S': m_keyS = false; break;
        case 'a': case 'A': m_keyA = false; break;
        case 'd': case 'D': m_keyD = false; break;
    }
}

void Camera::onMouseMove(int x, int y) {
    if (m_firstMouse) { m_lastMouseX = x; m_lastMouseY = y; m_firstMouse = false; }
    int dx = x - m_lastMouseX;
    int dy = y - m_lastMouseY;
    m_lastMouseX = x; m_lastMouseY = y;

    const float sensitivity = 0.1f;
    m_yaw += dx * sensitivity;
    m_pitch -= dy * sensitivity;
    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
}
