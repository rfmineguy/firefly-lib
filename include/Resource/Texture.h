#ifndef FL_RES_TEXTURE_H
#define FL_RES_TEXTURE_H
#include <glad/glad.h>

typedef struct Texture {
    char name[50];
    int width, height, channels;
    unsigned int handle;
    struct Texture* next;
} Texture;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

Texture FF_LoadTexture(const char*);
Texture FF_LoadTextureEx(const char*, GLint, GLint);
void FF_FreeTexture(Texture);

void FF_BindTexture(Texture);
void FF_BindTextureToUnit(Texture, int);
void FF_UnbindTexture();

#endif
