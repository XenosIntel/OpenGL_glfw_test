#ifndef SHADERPROGRAM_H_INCLUDED
#define SHADERPROGRAM_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>

class ShaderProgram
{
private:
    struct Shader
    {
        GLenum s_Type;
        const char* s_Path;
        GLuint shadHandle;

        Shader(GLenum type, const char* path) : s_Type(type), s_Path(path){};
    };

public:
    ShaderProgram();
    GLuint progHandle;

    void addShader(GLenum type, const char* path);
    void makeProgram();
    void useProgram();

    void uniBool(const char* name, GLboolean value) const;
    void uniInt(const char* name, GLint value) const;
    void uniFloat(const char* name, GLfloat value) const;

private:

    std::vector<Shader> shaders;

    void compileShader(Shader &shader);
};

#endif // SHADERPROGRAM_H_INCLUDED
