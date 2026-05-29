#pragma once

#include <memory>
#include "../renderer.h"

namespace Mini3D {

class ModernRenderer {
public:
    ModernRenderer();
    ~ModernRenderer();

    bool init(int w, int h, const char* title);
    void run();

private:
    int m_width;
    int m_height;
    const char* m_title;

    // placeholder for shader/GL state
};

} // namespace Mini3D
