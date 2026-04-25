#pragma once

class Birds {
public:
    // Create a bird flock. color defaults to dark gray, count defaults to 20, radius to 30
    Birds(float r = 0.1f, float g = 0.1f, float b = 0.1f, int count = 20, float radius = 30.0f);
    void init();
    void update(float dt);
    void render();

    // change color at runtime
    void setColor(float r, float g, float b);

private:
    float m_color[3];
    int m_count;
    float m_radius;
    float m_angle; // current rotation angle for the flock
};
