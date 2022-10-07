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
typedef struct _ResourcePool ResourcePool;

typedef enum {
	FF_TEXTURE, FF_SHADER, FF_SOUND
} ResourceType;
//
// New api
//

ResourcePool* FF_int_GetResourcePool();
void FF_InitResourceManager();
void FF_DeinitResourceManager();

void FF_PutTexture(Texture, const char*);
void FF_PutShader(Shader, const char*);
void FF_PutSound(Sound, const char*);

Texture FF_GetTexture(const char*);
Shader FF_GetShader(const char*);
Sound FF_GetSound(const char*);

bool FF_IsTextureLoaded(const char*);
bool FF_IsShaderLoaded(const char*);
bool FF_IsSoundLoaded(const char*);

//
// Old api
//
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