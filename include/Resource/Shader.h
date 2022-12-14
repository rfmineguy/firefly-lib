#ifndef FL_RES_SHADER_H
#define FL_RES_SHADER_H

//Shader
typedef struct Shader {
	char name[50];
	unsigned int vertId, fragId, programId;
    struct Shader* next;
} Shader;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources
Shader* LoadShader(const char*, const char*);
Shader* LoadShaderRaw(char*, const int, char*, const int);
void FreeShader(Shader*);

void BindShader(Shader*);
void UnbindShader();

void SetUniform1i(Shader*, const char*, int);
void SetUniform1f(Shader*, const char*, float);
void SetUniform2f(Shader*, const char*, float, float);
void SetUniform3f(Shader*, const char*, float, float, float);
void SetUniform4f(Shader*, const char*, float, float, float, float);
void SetUniform4fv(Shader*, const char*, float*);

int GetUniformLocation(Shader*, const char*);

#endif
