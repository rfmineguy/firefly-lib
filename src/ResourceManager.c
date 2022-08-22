#include "../include/Resource/ResourceManager.h"
#include "../include/IO/Log.h"
#include "../include/Core/HashTable.h"
#include <string.h>

typedef struct _ResourcePool {
    ht_t* shader_table;
    ht_t* texture_table;
    ht_t* atlas_table;
    ht_t* sound_table;
} ResourcePool;

static ResourcePool pool;

bool InitResourcePool() {
    pool.shader_table = ht_create();
    pool.texture_table = ht_create();
    pool.atlas_table = ht_create();
    pool.sound_table = ht_create();
    return true;
}

void DestroyResourcePool() {
    ht_free(pool.shader_table);
    ht_free(pool.texture_table);
    ht_free(pool.atlas_table);
    ht_free(pool.sound_table);
}

void PutShaderResource(Shader *s, const char *name) {
    if (s == NULL)
        return;
    ht_set(pool.shader_table, name, s);
}

bool IsShaderResourceLoaded(const char* name) {
    return ht_get(pool.shader_table, name) != NULL;
}

Shader* GetShaderResource(const char* name) {
    if (!IsShaderResourceLoaded(name)) {
        LOG_CRITICAL("Shader [%s] not loaded", name);
        return NULL;
    }
    return (Shader*) ht_get(pool.shader_table, name);
}

void FreeShaderResource(const char* name) {
    ht_del(pool.shader_table, name);
}

void PutTextureResource(Texture *t, const char *name) {
    if (t == NULL)
        return;
    ht_set(pool.texture_table, name, t);
}

bool IsTextureResourceLoaded(const char* name) {
    return ht_get(pool.texture_table, name) != NULL;
}

Texture* GetTextureResource(const char* name) {
    if (!IsTextureResourceLoaded(name)) {
        LOG_CRITICAL("Texture [%s] not loaded", name);
        return NULL;
    }
    return (Texture*) ht_get(pool.texture_table, name);
}

void FreeTextureResource(const char* name) {
    ht_del(pool.texture_table, name);
}

void PutAtlasResource(Atlas *t, const char *name) {
    if (t == NULL)
        return;
    ht_set(pool.texture_table, name, t);
}

bool IsAtlasResourceLoaded(const char* name) {
    return ht_get(pool.atlas_table, name) != NULL;
}

Atlas* GetAtlasResource(const char* name) {
    if (!IsAtlasResourceLoaded(name)) {
        LOG_CRITICAL("Atlas [%s] not loaded", name);
        return NULL;
    }
    return (Atlas*) ht_get(pool.atlas_table, name);
}

void FreeAtlasResource(const char* name) {
    ht_del(pool.atlas_table, name);
}

void PutSoundResource(Sound *s, const char *name) {
    if (s == NULL)
        return;
    ht_set(pool.sound_table, name, s);
}

bool IsSoundResourceLoaded(const char* name) {
    return ht_get(pool.sound_table, name) != NULL;
}

Sound* GetSoundResource(const char* name) {
    if (!IsSoundResourceLoaded(name)) {
        LOG_CRITICAL("Texture [%s] not loaded", name);
        return NULL;
    }
    return (Sound*) ht_get(pool.sound_table, name);
}

void FreeSoundResource(const char* name) {
    ht_del(pool.sound_table, name);
}
