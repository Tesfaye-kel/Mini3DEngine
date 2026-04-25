#include "renderer.h"
#include <cstdlib>

int main(int argc, char** argv) {
    Renderer renderer;
    renderer.init(argc, argv);
    glutMainLoop();
    return 0;
}
