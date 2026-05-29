#ifdef USE_GLFW

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace Mini3D {

Texture::~Texture() { if (m_id) glDeleteTextures(1, &m_id); }

bool Texture::loadFromFile(const std::string& path, bool srgb) {
    int w,h,n;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &n, 0);
    if (!data) { std::cerr<<"Failed to load texture: "<<path<<"\n"; return false; }

    GLenum format = (n==4?GL_RGBA:GL_RGB);
    GLenum internal = (srgb && n>=3) ? GL_SRGB8_ALPHA8 : GL_RGBA8;
    if (n==3) internal = srgb ? GL_SRGB8 : GL_RGB8;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D,0,internal,w,h,0,format,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(data);
    return true;
}

void Texture::bind(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

} // namespace Mini3D

#endif
