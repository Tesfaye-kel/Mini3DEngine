#include "Engine.h"
#include "../renderer.h"
#include <iostream>

namespace Mini3D {

Engine& Engine::Instance() {
    static Engine inst;
    return inst;
}

Engine::Engine() {}
Engine::~Engine() { Shutdown(); }

bool Engine::Init(int argc, char** argv) {
    m_renderer = std::make_unique<::Renderer>();
    m_renderer->init(argc, argv);
    return true;
}

void Engine::Run() {
    // For GLUT backend we just enter the main loop
    // The renderer registered callbacks inside init()
    // Keep this simple for now.
#ifdef _WIN32
    // On Windows glutMainLoop is available
#endif
    // Call glutMainLoop from main.cpp
}

void Engine::Shutdown() {
    m_renderer.reset();
}

::Renderer* Engine::GetRenderer() { return m_renderer.get(); }

} // namespace Mini3D
