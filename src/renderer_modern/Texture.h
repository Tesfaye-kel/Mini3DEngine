#pragma once
#ifdef USE_GLFW

#include <string>
#include <glad/glad.h>

namespace Mini3D {

class Texture {
public:
    Texture() = default;
    ~Texture();

    bool loadFromFile(const std::string& path, bool srgb = false);
    void bind(int unit = 0) const;
    GLuint id() const { return m_id; }

private:
    GLuint m_id = 0;
};

} // namespace Mini3D

#endif
