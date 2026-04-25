#pragma once

#include <GL/glut.h>
#include <memory>

class Camera;
class Terrain;
class House;
class Trees;
class Birds;
class PlaneSystem;
class WaterSystem;
class LightSystem;
class AnimationSystem;
class Scene2D;
class CarSystem;
class GreenArea;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init(int argc, char** argv);
    void resize(int w, int h);
    void update(float dt);
    void render();

    // input
    void onKeyDown(unsigned char key, int x, int y);
    void onKeyUp(unsigned char key, int x, int y);
    void onMouseMove(int x, int y);

    float getTime() const { return m_time; }

private:
    void initGL();
    void initScene();

    int m_width;
    int m_height;
    float m_time; // seconds

    Camera* m_camera;
    Terrain* m_terrain;
    House* m_house;
    Trees* m_trees;
    Birds* m_birds;
    Birds* m_birds2; // second flock with different color
    PlaneSystem* m_plane;
    WaterSystem* m_water;
    LightSystem* m_lights;
    AnimationSystem* m_anim;
    CarSystem* m_cars;
    GreenArea* m_greenArea;

    // 2D overlay
    // forward declare functions for the simple 2D overlay
};
