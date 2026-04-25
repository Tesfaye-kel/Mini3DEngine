#pragma once

#include <GL/glut.h>

class Camera {
public:
    Camera();
    void setViewport(int w, int h);
    void applyView();
    void update(float dt);

    void onKeyDown(unsigned char key);
    void onKeyUp(unsigned char key);
    void onMouseMove(int x, int y);

private:
    float m_pos[3];
    float m_yaw;
    float m_pitch;
    float m_speed;

    bool m_keyW, m_keyA, m_keyS, m_keyD;
    int m_lastMouseX, m_lastMouseY;
    bool m_firstMouse;
};
