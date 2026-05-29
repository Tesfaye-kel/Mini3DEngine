#include "core/Engine.h"
#include <cstdlib>
#include <GL/glut.h>

int main(int argc, char** argv) {
    Mini3D::Engine& engine = Mini3D::Engine::Instance();
    if (!engine.Init(argc, argv)) return EXIT_FAILURE;
    // Enter GLUT main loop (callbacks were registered by Renderer)
    glutMainLoop();
    engine.Shutdown();
    return EXIT_SUCCESS;
}
