#include "../include/Resource/Shader.h"
#include "../include/IO/File.h"
#include "../include/IO/Log.h"
#include <glad/glad.h>
#include <string.h>

void ProcessShaderInternal(unsigned int* id, char* contents, GLenum shaderType, const int length) {
    *id = glCreateShader(shaderType);
    LOG_DEBUG("Processing shader: %d", *id);
    glShaderSource(*id, 1, (const char *const *)&contents, &length);
    LOG_DEBUG("Loaded the shader source");
    glCompileShader(*id);
    LOG_DEBUG("Compiled shader");

    GLint success;
    char infoLog[500];
    glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*id, 500, NULL, infoLog);
        printf("%s", contents);
        if (shaderType == GL_VERTEX_SHADER) {
            LOG_CRITICAL("Vertex shader compilation failed.");
            LOG_CRITICAL("\t%s", infoLog);
        }
        if (shaderType == GL_FRAGMENT_SHADER) {
            LOG_CRITICAL("Fragment shader compilation failed.");
            LOG_CRITICAL("\t%s", infoLog);
        }
    }
}

void LinkShaderInteral(Shader* pShader) {
    pShader->programId = glCreateProgram();
    glAttachShader(pShader->programId, pShader->vertId);
    glAttachShader(pShader->programId, pShader->fragId);
    glLinkProgram(pShader->programId);

    GLint success;
    char infoLog[500];
    glGetProgramiv(pShader->programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(pShader->programId, 500, NULL, infoLog);
        printf("ERROR:SHADER::PROGRAM::LINK_FAIL\n\t%s\n", infoLog);
    }

    glDeleteShader(pShader->vertId);
    glDeleteShader(pShader->fragId);
}

Shader* LoadShader(const char* root_path, const char* name) {
    char vert_path[255] = {}, frag_path[255] = {};
    strcat(vert_path, root_path);
    strcat(vert_path, name);
    strcat(vert_path, ".vert");
    strcat(frag_path, root_path);
    strcat(frag_path, name);
    strcat(frag_path, ".frag");

    LOG_INFO("Opening [%s] and [%s]", vert_path, frag_path);

    FILE* f = SetReadStream(FileOpen(vert_path, READ));
    char* vert_source = Read(NULL);
    FileClose(f);

    f = SetReadStream(FileOpen(frag_path, READ));
    char* frag_source = Read(NULL);
    FileClose(f);

    //strlen is allowed as these source strings will be null terminated
    Shader *pShader = LoadShaderRaw(vert_source, strlen(vert_source), frag_source, strlen(frag_source));
    LOG_DEBUG("Linked the shader [%s] from [%s]", name, root_path);

    free(vert_source);
    vert_source = NULL;
    free(frag_source);
    frag_source = NULL;
    return pShader;
}

Shader* LoadShaderRaw(char *raw_vert_source, const int vert_length, char *raw_frag_source, const int frag_length) {
    LOG_DEBUG("LoadShaderRaw()");
    //fwrite(raw_frag_source, sizeof(char), frag_length, stdout);
    //fwrite(raw_vert_source, sizeof(char), vert_length, stdout);

    Shader *pShader = malloc(sizeof(*pShader));
    memset(pShader, 0, sizeof(*pShader));
    LOG_DEBUG("Begin Processing Shader");
    ProcessShaderInternal(&pShader->vertId, raw_vert_source, GL_VERTEX_SHADER, vert_length);
    ProcessShaderInternal(&pShader->fragId, raw_frag_source, GL_FRAGMENT_SHADER, frag_length);
    LOG_DEBUG("End Processing Shader");
    LinkShaderInteral(pShader);
    return pShader;
}

void FreeShader(Shader *pShader) {
    glDeleteProgram(pShader->programId);
    free(pShader);
    pShader = NULL;
}

void BindShader(Shader *pShader) {
    glUseProgram(pShader->programId);
}

void UnbindShader() {
    glUseProgram(0);
}

void SetUniform1f(Shader *pShader, const char *name, float a) {
    int loc = GetUniformLocation(pShader, name);
    glUniform1f(loc, a);
}

void SetUniform2f(Shader *pShader, const char *name, float a, float b) {
    int loc = GetUniformLocation(pShader, name);
    glUniform2f(loc, a, b);
}

void SetUniform3f(Shader *pShader, const char *name, float a, float b, float c) {
    int loc = GetUniformLocation(pShader, name);
    glUniform3f(loc, a, b, c);
}

void SetUniform4f(Shader *pShader, const char *name, float a, float b, float c, float d) {
    int loc = GetUniformLocation(pShader, name);
    glUniform4f(loc, a, b, c, d);
}

void SetUniform4fv(Shader *pShader, const char *name, float* mat) {
    int loc = GetUniformLocation(pShader, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);    
}

int GetUniformLocation(Shader *pShader, const char *name) {
    int location = glGetUniformLocation(pShader->programId, name);
    if (location == -1) {
        fprintf(stderr, "Uniform [%s] not found\n", name);
    }
    return location;
}
