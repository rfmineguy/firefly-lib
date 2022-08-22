#ifndef FL_RESRES_MAN_H
#define FL_RESRES_MAN_H

#include "Atlas.h"
#include "Shader.h"
#include "Sound.h"
#include "Texture.h"
#include <stdbool.h>

/*
 #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources
 */

//Resource Pool
typedef enum {
	ALL=0, SHADER=1, TEXTURE=2, ATLAS=4, SOUND=8
} ResourceType;

// abstract type
typedef struct _ResourcePool ResourcePool;

bool InitResourcePool();
void DestroyResourcePool();

void PutShaderResource(Shader*, const char*);
bool IsShaderResourceLoaded(const char*);
Shader* GetShaderResource(const char*);
void FreeShaderResource(const char*);

void PutTextureResource(Texture*, const char*);
bool IsTextureResourceLoaded(const char*);
Texture* GetTextureResource(const char*);
void FreeTextureResource(const char*);

void PutAtlasResource(Atlas*, const char*);
bool IsAtlasResourceLoaded(const char*);
Atlas* GetAtlasResource(const char*);
void FreeAtlasResource(const char*);

void PutSoundResource(Sound*, const char*);
bool IsSoundResourceLoaded(const char*);
Sound* GetSoundResource(const char*);
void FreeSoundResource(const char*);

#endif
