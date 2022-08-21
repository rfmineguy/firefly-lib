#include "../include/Resource/Shader.h"
#include "../include/IO/File.h"
#include "../include/IO/Log.h"
#include <glad/glad.h>
#include <string.h>

void ProcessShaderInternal(unsigned int* id, char* contents, GLenum shaderType) {
    *id = glCreateShader(shaderType);
    glShaderSource(*id, 1, &contents, NULL);
    glCompileShader(*id);

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
    glGetShaderiv(pShader->programId, GL_LINK_STATUS, &success);
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

    Shader* pShader = (Shader*) malloc(sizeof(*pShader));
    memset(pShader, 0, sizeof(*pShader));
    ProcessShaderInternal(&pShader->vertId, vert_source, GL_VERTEX_SHADER);
    ProcessShaderInternal(&pShader->fragId, frag_source, GL_FRAGMENT_SHADER);
    LinkShaderInteral(pShader);
    LOG_DEBUG("Linked the shader [%s] from [%s]", name, root_path);

    free(vert_source);
    vert_source = NULL;
    free(frag_source);
    frag_source = NULL;
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
