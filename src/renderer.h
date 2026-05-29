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

/**
 * Lightweight renderer used by the example engine. This is a compatibility
 * layer that currently uses GLUT and immediate-mode for the demo scene. It
 * is organized to be replaced by a modern Renderer later.
 */
class Renderer {
public:
    Renderer();
    ~Renderer();

    /** Initialize GL/windowing and the scene. */
    void init(int argc, char** argv);

    /** Window resize callback. */
    void resize(int w, int h);

    /** Update per-frame state. */
    void update(float dt);

    /** Render the current frame. */
    void render();

    // input callbacks
    void onKeyDown(unsigned char key, int x, int y);
    void onKeyUp(unsigned char key, int x, int y);
    void onMouseMove(int x, int y);

    float getTime() const { return m_time; }

private:
    void initGL();
    void initScene();

    int m_width = 800;
    int m_height = 600;
    float m_time = 0.0f; // seconds

    Camera* m_camera = nullptr;
    Terrain* m_terrain = nullptr;
    House* m_house = nullptr;
    Trees* m_trees = nullptr;
    Birds* m_birds = nullptr;
    Birds* m_birds2 = nullptr; // second flock with different color
    PlaneSystem* m_plane = nullptr;
    WaterSystem* m_water = nullptr;
    LightSystem* m_lights = nullptr;
    AnimationSystem* m_anim = nullptr;
    CarSystem* m_cars = nullptr;
    GreenArea* m_greenArea = nullptr;
};
