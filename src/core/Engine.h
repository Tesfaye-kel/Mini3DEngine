#pragma once

#include <memory>

// Forward declare the global Renderer class (defined in src/renderer.h)
class Renderer;

namespace Mini3D {

/**
 * Engine singleton managing application lifecycle.
 */
class Engine {
public:
    /** Get the singleton instance. */
    static Engine& Instance();

    /** Initialize the engine and subsystems. */
    bool Init(int argc, char** argv);

    /** Run the main loop (for GLUT this calls glutMainLoop). */
    void Run();

    /** Shutdown and cleanup resources. */
    void Shutdown();

    ::Renderer* GetRenderer();

private:
    Engine();
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    std::unique_ptr<::Renderer> m_renderer;
};

} // namespace Mini3D
