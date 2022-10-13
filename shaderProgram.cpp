#include "shaderProgram.h"

ShaderProgram::ShaderProgram(){};

void ShaderProgram::addShader(GLenum type, const char* path)
{
    shaders.push_back(Shader(type, path));
}

void ShaderProgram::compileShader(Shader &shader)
{
    GLchar *shaderSource;
    std::ifstream file(shader.s_Path, std::ifstream::binary);

    if(!file)
    {
        std::cout << "File not found: " << shader.s_Path << std::endl;
    }

    file.seekg(0, file.end);
    int lenght = file.tellg();
    file.seekg(0, file.beg);

    shaderSource = new GLchar[lenght];

    file.read(shaderSource, lenght);
    shaderSource[lenght] = '\0';
    file.close();

    shader.shadHandle = glCreateShader(shader.s_Type);
    glShaderSource(shader.shadHandle, 1, &shaderSource, NULL);
    delete[] shaderSource;
    glCompileShader(shader.shadHandle);

    int success;
    char infoLog[512];
    glGetShaderiv(shader.shadHandle, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader.shadHandle, 512, NULL, infoLog);
        std::cout << "Shader compilation failed: " << infoLog << std::endl;
    }
}

void ShaderProgram::makeProgram()
{
    progHandle = glCreateProgram();

    for(std::vector<Shader>::iterator it = shaders.begin(); it != shaders.end(); ++it)
    {
        compileShader(*it);
    }

    for(std::vector<Shader>::iterator it = shaders.begin(); it != shaders.end(); ++it)
    {
        glAttachShader(progHandle, it->shadHandle);
    }

    glLinkProgram(progHandle);

    int success;
    char infoLog[512];
    glGetProgramiv(progHandle, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(progHandle, 512, NULL, infoLog);
        std::cout << "Program linking failed: " << infoLog << std::endl;
    }

    for(std::vector<Shader>::iterator it = shaders.begin(); it != shaders.end(); ++it)
    {
        glDeleteShader(it->shadHandle);
    }

    shaders.clear();
}

void ShaderProgram::useProgram()
{
    glUseProgram(progHandle);
}

void ShaderProgram::uniBool(const char* name, GLboolean value) const
{
    glUniform1i(glGetUniformLocation(progHandle, name), (int)value);
}

void ShaderProgram::uniInt(const char* name, GLint value) const
{
    glUniform1i(glGetUniformLocation(progHandle, name), value);
}

void ShaderProgram::uniFloat(const char* name, GLfloat value) const
{
    glUniform1f(glGetUniformLocation(progHandle, name), value);
}
