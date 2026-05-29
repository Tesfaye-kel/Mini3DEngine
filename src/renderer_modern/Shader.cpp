#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef USE_GLFW
#include <glad/glad.h>
#else
#include <Windows.h>
#include <GL/gl.h>
#endif

namespace Mini3D {

static std::string readFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) return {};
    std::ostringstream ss; ss << in.rdbuf();
    return ss.str();
}

Shader::~Shader() {
#ifdef USE_GLFW
    if (m_program) glDeleteProgram(m_program);
#endif
}

bool Shader::loadFromFiles(const std::string& vertPath, const std::string& fragPath) {
    std::string vs = readFile(vertPath);
    std::string fs = readFile(fragPath);
    if (vs.empty() || fs.empty()) return false;

#ifdef USE_GLFW
    unsigned int vsId = glCreateShader(GL_VERTEX_SHADER);
    const char* vsSrc = vs.c_str();
    glShaderSource(vsId, 1, &vsSrc, nullptr);
    glCompileShader(vsId);
    int ok; glGetShaderiv(vsId, GL_COMPILE_STATUS, &ok);
    if (!ok) { char buf[1024]; glGetShaderInfoLog(vsId,1024,nullptr,buf); std::cerr<<"VS compile error:"<<buf<<"\n"; return false; }

    unsigned int fsId = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsSrc = fs.c_str();
    glShaderSource(fsId, 1, &fsSrc, nullptr);
    glCompileShader(fsId);
    glGetShaderiv(fsId, GL_COMPILE_STATUS, &ok);
    if (!ok) { char buf[1024]; glGetShaderInfoLog(fsId,1024,nullptr,buf); std::cerr<<"FS compile error:"<<buf<<"\n"; return false; }

    m_program = glCreateProgram();
    glAttachShader(m_program, vsId);
    glAttachShader(m_program, fsId);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
    if (!ok) { char buf[1024]; glGetProgramInfoLog(m_program,1024,nullptr,buf); std::cerr<<"Link error:"<<buf<<"\n"; return false; }
    glDeleteShader(vsId); glDeleteShader(fsId);
    return true;
#else
    // No-op without GLAD
    (void)vertPath; (void)fragPath; return false;
#endif
}

void Shader::bind() const {
#ifdef USE_GLFW
    glUseProgram(m_program);
#endif
}
void Shader::unbind() const {
#ifdef USE_GLFW
    glUseProgram(0);
#endif
}

void Shader::setInt(const std::string& name, int value) const {
#ifdef USE_GLFW
    int loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(loc, value);
#endif
}
void Shader::setFloat(const std::string& name, float value) const {
#ifdef USE_GLFW
    int loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1f(loc, value);
#endif
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const {
#ifdef USE_GLFW
    int loc = glGetUniformLocation(m_program, name.c_str());
    glUniform3f(loc, x,y,z);
#endif
}

void Shader::setMat4(const std::string& name, const float* mat) const {
#ifdef USE_GLFW
    int loc = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
#endif
}

} // namespace Mini3D
