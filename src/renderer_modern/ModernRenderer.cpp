#include "ModernRenderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include <iostream>

#ifdef USE_GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#include "Mesh.h"
// small math helpers (avoid requiring GLM)
#include <array>
#include <cmath>

static std::array<float,16> perspective(float fovy, float aspect, float znear, float zfar) {
    float f = 1.0f / tanf(fovy * 0.5f);
    std::array<float,16> m{};
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (zfar + znear) / (znear - zfar);
    m[11] = -1.0f;
    m[14] = (2.0f * zfar * znear) / (znear - zfar);
    return m;
}

static std::array<float,16> lookAt(const std::array<float,3>& eye, const std::array<float,3>& center, const std::array<float,3>& up) {
    auto sub = [](const std::array<float,3>& a, const std::array<float,3>& b){ return std::array<float,3>{a[0]-b[0], a[1]-b[1], a[2]-b[2]}; };
    auto norm = [](std::array<float,3> v){ float l = sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]); return std::array<float,3>{v[0]/l,v[1]/l,v[2]/l}; };
    auto cross = [](const std::array<float,3>& a, const std::array<float,3>& b){ return std::array<float,3>{ a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0] }; };
    auto f = norm(sub(center, eye));
    auto s = norm(cross(f, up));
    auto u = cross(s, f);
    std::array<float,16> m{};
    m[0]=s[0]; m[4]=s[1]; m[8]=s[2]; m[12]=-(s[0]*eye[0]+s[1]*eye[1]+s[2]*eye[2]);
    m[1]=u[0]; m[5]=u[1]; m[9]=u[2]; m[13]=-(u[0]*eye[0]+u[1]*eye[1]+u[2]*eye[2]);
    m[2]=-f[0]; m[6]=-f[1]; m[10]=-f[2]; m[14]=(f[0]*eye[0]+f[1]*eye[1]+f[2]*eye[2]);
    m[3]=0; m[7]=0; m[11]=0; m[15]=1;
    return m;
}

// static resources and implementation guarded by USE_GLFW
#ifdef USE_GLFW

static Texture s_albedo, s_rough, s_metallic, s_ao;
static Mesh* s_ground = nullptr;
static Mesh* s_house = nullptr;
static Mesh* s_pool = nullptr;

namespace Mini3D {

ModernRenderer::ModernRenderer() : m_width(1280), m_height(720), m_title("Mini3D Modern") {}
ModernRenderer::~ModernRenderer() {}

bool ModernRenderer::init(int w, int h, const char* title) {
    m_width = w; m_height = h; m_title = title;
    if (!glfwInit()) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (!window) { glfwTerminate(); return false; }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cerr<<"Failed to init GLAD\n"; return false; }

    glViewport(0,0,m_width,m_height);
    glEnable(GL_DEPTH_TEST);
    // load shader
    static Shader s;
    if (!s.loadFromFiles("shaders/pbr.vert","shaders/pbr.frag")) {
        std::cerr<<"Failed to load shader"<<std::endl;
    }

    // load simple textures
    s_albedo.loadFromFile("assets/wood_albedo.jpg", true);
    s_rough.loadFromFile("assets/wood_rough.jpg", false);
    s_metallic.loadFromFile("assets/wood_metal.jpg", false);
    s_ao.loadFromFile("assets/wood_ao.jpg", false);

    // create simple geometry
    s_ground = Mesh::createPlane(50.0f);
    s_house = Mesh::createCube(4.0f,2.0f,6.0f);
    s_pool = Mesh::createPlane(6.0f);

    // main loop moved to run()
    return true;
}

void ModernRenderer::run() {
    GLFWwindow* win = glfwGetCurrentContext();
    Shader s; s.loadFromFiles("shaders/pbr.vert","shaders/pbr.frag");
    auto projArr = perspective(60.0f * 3.14159265f / 180.0f, (float)m_width/(float)m_height, 0.1f, 1000.0f);
    std::array<float,3> eye{0.0f,5.0f,15.0f};
    std::array<float,3> center{0.0f,1.0f,0.0f};
    std::array<float,3> up{0.0f,1.0f,0.0f};
    auto viewArr = lookAt(eye, center, up);
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glClearColor(0.53f,0.7f,0.9f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s.bind();
        s.setVec3("uLightDir", -0.3f, -1.0f, -0.2f);
        s.setVec3("uLightColor", 1.0f, 0.98f, 0.93f);
        s.setVec3("uCamPos", 0.0f, 5.0f, 15.0f);

        // set matrices
        s.setMat4("uProj", projArr.data());
        s.setMat4("uView", viewArr.data());

        // ground: identity model
        std::array<float,16> modelArr{}; modelArr[0]=1; modelArr[5]=1; modelArr[10]=1; modelArr[15]=1;
        s.setMat4("uModel", modelArr.data());
        s.setInt("albedoMap", 0);
        s_albedo.bind(0);
        s.setInt("roughnessMap", 1);
        s_rough.bind(1);
        s.setInt("metallicMap", 2);
        s_metallic.bind(2);
        s.setInt("aoMap", 3);
        s_ao.bind(3);
        if (s_ground) s_ground->draw();

        // house: translate up by 1.0
        std::array<float,16> modelHouse{}; modelHouse[0]=1; modelHouse[5]=1; modelHouse[10]=1; modelHouse[15]=1; modelHouse[13]=1.0f;
        s.setMat4("uModel", modelHouse.data());
        if (s_house) s_house->draw();

        // pool: translate to (8,0.01,5)
        std::array<float,16> modelPool{}; modelPool[0]=1; modelPool[5]=1; modelPool[10]=1; modelPool[15]=1; modelPool[12]=8.0f; modelPool[14]=5.0f; modelPool[13]=0.01f;
        s.setMat4("uModel", modelPool.data());
        if (s_pool) s_pool->draw();

        s.unbind();
        glfwSwapBuffers(win);
    }
}

} // namespace Mini3D

#else

// Stubs when USE_GLFW is not enabled
namespace Mini3D {
ModernRenderer::ModernRenderer() : m_width(800), m_height(600), m_title("Mini3D") {}
ModernRenderer::~ModernRenderer() {}
bool ModernRenderer::init(int, int, const char*) { return false; }
void ModernRenderer::run() {}
} // namespace Mini3D

#endif
