#pragma once

#ifdef USE_GLFW

#include <vector>
#include <glad/glad.h>

namespace Mini3D {

class Mesh {
public:
    Mesh();
    ~Mesh();

    void upload(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    void draw() const;

    static Mesh* createPlane(float size = 10.0f);
    static Mesh* createCube(float sx=1.0f, float sy=1.0f, float sz=1.0f);

private:
    GLuint m_vao = 0, m_vbo = 0, m_ebo = 0;
    GLsizei m_indexCount = 0;
};

} // namespace Mini3D

#endif
