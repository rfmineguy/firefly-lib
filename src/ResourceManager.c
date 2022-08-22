#include "../include/Resource/ResourceManager.h"
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
    ht_set(pool.shader_table, name, s);
}

Shader* GetShaderResource(const char* name) {
    return (Shader*) ht_get(pool.shader_table, name);
}

void FreeShaderResource(const char* name) {
    ht_del(pool.shader_table, name);
}
