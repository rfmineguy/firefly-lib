#ifndef FL_RES_TEXTURE_H
#define FL_RES_TEXTURE_H

typedef struct {
	
} Texture;

// #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources

Texture* LoadTexture(const char*);
void FreeTexture(Texture*);

void BindTexture(Texture*);
void BindTextureToUnit(Texture*, int);

void UnbindTexture();

#endif
