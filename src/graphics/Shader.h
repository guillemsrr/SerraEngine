#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
public:
    Shader() = default;
    ~Shader();

    void LoadVertexFragment(const std::string& shader, const std::string& fragmentShader);
    void LoadCompute(const std::string& computePath);

    void Use() const;
    void Unbind() const;
    void Destroy();

    GLuint GetID() const
    {
        return _program;
    }

    bool IsCompiled() const;

private:
    GLuint _program = 0;

    GLint _success = GL_FALSE;

    bool CompileShader(GLuint& shaderID, GLenum type, const std::string& code);
    std::string LoadShader(const std::string& shader);
};