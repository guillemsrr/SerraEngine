#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL3/SDL_log.h>
#include <filesystem>

Shader::~Shader()
{
    Destroy();
}

void Shader::LoadVertexFragment(const std::string& shader, const std::string& fragmentShader)
{
    Destroy();

    std::string vertCode = LoadShader(shader);
    std::string fragCode = LoadShader(fragmentShader);
    if (vertCode.empty() || fragCode.empty())
        return;

    GLuint vShader, fShader;
    if (!CompileShader(vShader, GL_VERTEX_SHADER, vertCode))
        return;
    if (!CompileShader(fShader, GL_FRAGMENT_SHADER, fragCode))
        return;

    _program = glCreateProgram();
    glAttachShader(_program, vShader);
    glAttachShader(_program, fShader);
    glLinkProgram(_program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    glGetProgramiv(_program, GL_LINK_STATUS, &_success);
    if (!_success)
    {
        char infoLog[512];
        glGetProgramInfoLog(_program, 512, nullptr, infoLog);
        SDL_Log("Shader linking error: %s", infoLog);
        Destroy();
        return;
    }
}

void Shader::LoadCompute(const std::string& computePath)
{
    Destroy();

    std::string compCode = LoadShader(computePath);
    if (compCode.empty())
        return;

    GLuint cShader;
    if (!CompileShader(cShader, GL_COMPUTE_SHADER, compCode))
        return;

    _program = glCreateProgram();
    glAttachShader(_program, cShader);
    glLinkProgram(_program);

    glDeleteShader(cShader);

    glGetProgramiv(_program, GL_LINK_STATUS, &_success);
    if (!_success)
    {
        char infoLog[512];
        glGetProgramInfoLog(_program, 512, nullptr, infoLog);
        SDL_Log("Compute shader linking error: %s", infoLog);
        Destroy();
    }
}

bool Shader::CompileShader(GLuint& shaderID, GLenum type, const std::string& code)
{
    shaderID = glCreateShader(type);
    const char* src = code.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        SDL_Log("%s shader compile error: %s",
                (type == GL_VERTEX_SHADER
                     ? "Vertex"
                     : type == GL_FRAGMENT_SHADER
                     ? "Fragment"
                     : type == GL_COMPUTE_SHADER
                     ? "Compute"
                     : "Unknown"),
                infoLog);
        glDeleteShader(shaderID);
        return false;
    }
    return true;
}

std::string Shader::LoadShader(const std::string& shader)
{
    std::filesystem::path shadersPath = std::filesystem::absolute("shaders/" + shader);
    std::ifstream file(shadersPath);
    if (!file.is_open())
    {
        SDL_Log("Failed to open shader file: %s", shader.c_str());
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::Use() const
{
    glUseProgram(_program);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::Destroy()
{
    _success = GL_FALSE;
    if (_program)
    {
        glDeleteProgram(_program);
        _program = 0;
    }
}

bool Shader::IsCompiled() const
{
    return _success == GL_TRUE;
}