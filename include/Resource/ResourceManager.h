#ifndef FL_RESRES_MAN_H
#define FL_RESRES_MAN_H

#include "Atlas.h"
#include "Shader.h"
#include "Sound.h"
#include "Texture.h"

/*
 #define AUTO_RESOURCE_REGISTER for automatic inclusion of individually loaded resources
 */

//Resource Pool
typedef enum {
	ALL=0, SHADER=1, TEXTURE=2, ATLAS=4, SOUND=8
} ResourceType;

// abstract type
typedef struct {
	Shader* pShaders;
	Texture* pTextures;
	Atlas* pAtlases;
	Sound* pSounds;
} ResourcePool;

int PutShaderResource(Shader*, const char*);
bool IsShaderResourceLoaded(const char*);
Shader* GetShaderResource(const char*);

int PutTextureResource(Texture*, const char*);
bool IsTextureResourceLoaded(const char*);
Texture* GetTextureResource(const char*);

int PutAtlasResource(Atlas*, const char*);
bool IsAtlasResourceLoaded(const char*);
Atlas* GetAtlasResource(const char*);

int PutSoundResource(Sound*, const char*);
bool IsSoundResourceLoaded(const char*);
Sound* GetSoundResource(const char*);

void FreeAllResources(ResourceType);

#endif
