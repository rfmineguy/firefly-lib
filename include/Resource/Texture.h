#ifndef FL_RES_TEXTURE_H
#define FL_RES_TEXTURE_H
#include "../../libs/glad-rf/include/glad/glad.h"

typedef struct Texture {
    char name[50];
    int width, height, channels;
    unsigned int handle;
    struct Texture* next;
} Texture;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

Texture* LoadTexture(const char*);
Texture* LoadTextureEx(const char*, GLint, GLint);
void FreeTexture(Texture*);

void BindTexture(Texture*);
void BindTextureToUnit(Texture*, int);

void UnbindTexture();

#endif
