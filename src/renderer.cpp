#include "renderer.h"
#include "camera.h"
#include "terrain.h"
#include "house.h"
#include "trees.h"
#include "birds.h"
#include "plane.h"
#include "water.h"
#include "lighting.h"
#include "animation.h"
#include "car.h"
#include "greenarea.h"
#include "scene2d.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

static Renderer* g_instance = nullptr;

Renderer::Renderer()
    : m_width(800), m_height(600), m_time(0.0f),
      m_camera(nullptr), m_terrain(nullptr), m_house(nullptr), m_trees(nullptr), m_birds(nullptr), m_plane(nullptr), m_water(nullptr), m_lights(nullptr), m_anim(nullptr)
{
}

Renderer::~Renderer() {
    // cleanup
}

void Renderer::init(int argc, char** argv) {
    if (g_instance) return;
    g_instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(m_width, m_height);
    glutCreateWindow("ForestLuxuryWorld");

    initGL();
    initScene();

    // register callbacks
    glutDisplayFunc([](){ if (g_instance) g_instance->render(); });
    glutReshapeFunc([](int w, int h){ if (g_instance) g_instance->resize(w,h); });
    glutIdleFunc([](){ if (g_instance) glutPostRedisplay(); });
    glutKeyboardFunc([](unsigned char k, int x, int y){ if (g_instance) g_instance->onKeyDown(k,x,y); });
    glutKeyboardUpFunc([](unsigned char k, int x, int y){ if (g_instance) g_instance->onKeyUp(k,x,y); });
    glutPassiveMotionFunc([](int x, int y){ if (g_instance) g_instance->onMouseMove(x,y); });
}

void Renderer::initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE);

    glClearColor(0.5f, 0.7f, 0.9f, 1.0f); // sky-ish
}

void Renderer::initScene() {
    m_camera = new Camera();
    m_camera->setViewport(m_width, m_height);

    m_terrain = new Terrain(); m_terrain->init();
    m_house = new House(); m_house->init();
    m_trees = new Trees(); m_trees->init();
    m_birds = new Birds(0.1f,0.1f,0.1f,20,30.0f); m_birds->init();
    m_birds2 = new Birds(0.8f,0.8f,0.1f,12,20.0f); m_birds2->init();
    m_plane = new PlaneSystem(); m_plane->init();
    m_water = new WaterSystem(); m_water->init();
    m_lights = new LightSystem(); m_lights->init();
    m_anim = new AnimationSystem(); m_anim->init();
    m_cars = new CarSystem(); m_cars->init();
    m_greenArea = new GreenArea(); m_greenArea->init();
    Scene2D_init();
}

void Renderer::resize(int w, int h) {
    m_width = w; m_height = h;
    glViewport(0,0,w,h);
    m_camera->setViewport(w,h);
}

void Renderer::update(float dt) {
    m_time += dt;
    if (m_camera) m_camera->update(dt);
    if (m_terrain) m_terrain->update(dt);
    if (m_house) m_house->update(dt);
    if (m_trees) m_trees->update(dt);
    if (m_birds) m_birds->update(dt);
    if (m_birds2) m_birds2->update(dt);
    if (m_plane) m_plane->update(dt);
    if (m_water) m_water->update(dt);
    if (m_lights) m_lights->update(dt);
    if (m_anim) m_anim->update(dt);
    if (m_cars) m_cars->update(dt);
    if (m_greenArea) m_greenArea->update(dt);
    Scene2D_update(dt);
}

void Renderer::render() {
    static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    int now = glutGet(GLUT_ELAPSED_TIME);
    float dt = (now - lastTime) * 0.001f;
    lastTime = now;

    update(dt);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)m_width / (double)m_height, 0.1, 2000.0);

    // apply lights
    if (m_lights) m_lights->apply();

    // view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (m_camera) m_camera->applyView();

    // render scene
    if (m_terrain) m_terrain->render();
    if (m_house) m_house->render();
    if (m_trees) m_trees->render();
    if (m_water) m_water->render();
    if (m_birds) m_birds->render();
    if (m_birds2) m_birds2->render();
    if (m_plane) m_plane->render();
    if (m_cars) m_cars->render();
    if (m_greenArea) m_greenArea->render();
    Scene2D_render();

    glutSwapBuffers();
}

void Renderer::onKeyDown(unsigned char key, int x, int y) {
    if (m_camera) m_camera->onKeyDown(key);
}
void Renderer::onKeyUp(unsigned char key, int x, int y) { if (m_camera) m_camera->onKeyUp(key); }
void Renderer::onMouseMove(int x, int y) { if (m_camera) m_camera->onMouseMove(x,y); }
