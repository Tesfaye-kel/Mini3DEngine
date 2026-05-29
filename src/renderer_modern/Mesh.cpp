#ifdef USE_GLFW

#include "Mesh.h"
#include <vector>

namespace Mini3D {

Mesh::Mesh() {}
Mesh::~Mesh() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
}

void Mesh::upload(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    m_indexCount = (GLsizei)indices.size();
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // vertex layout: pos(3), normal(3), uv(2)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));

    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh* Mesh::createPlane(float size) {
    float half = size*0.5f;
    std::vector<float> v = {
        -half, 0.0f, -half, 0,1,0, 0,0,
         half, 0.0f, -half, 0,1,0, 1,0,
         half, 0.0f,  half, 0,1,0, 1,1,
        -half, 0.0f,  half, 0,1,0, 0,1,
    };
    std::vector<unsigned int> idx = {0,1,2, 2,3,0};
    Mesh* m = new Mesh();
    m->upload(v, idx);
    return m;
}

Mesh* Mesh::createCube(float sx, float sy, float sz) {
    // Simple cube centered at origin
    std::vector<float> v = {
        // positions        normals       uv
        -sx,-sy,-sz,  0,0,-1, 0,0,
         sx,-sy,-sz,  0,0,-1, 1,0,
         sx, sy,-sz,  0,0,-1, 1,1,
        -sx, sy,-sz,  0,0,-1, 0,1,
        // ... other faces omitted for brevity in this demo
    };
    std::vector<unsigned int> idx = {0,1,2, 2,3,0};
    Mesh* m = new Mesh();
    m->upload(v, idx);
    return m;
}

} // namespace Mini3D

#endif
