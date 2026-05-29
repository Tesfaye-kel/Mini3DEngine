#pragma once

#include <string>
#include <unordered_map>

namespace Mini3D {

/** Simple RAII shader program wrapper */
class Shader {
public:
    Shader() = default;
    ~Shader();

    bool loadFromFiles(const std::string& vertPath, const std::string& fragPath);
    void bind() const;
    void unbind() const;

    // uniforms
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setMat4(const std::string& name, const float* mat) const;

private:
    unsigned int m_program = 0;
    mutable std::unordered_map<std::string,int> m_cache;
};

} // namespace Mini3D
