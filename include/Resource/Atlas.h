#ifndef FL_RES_ATLAS_H
#define FL_RES_ATLAS_H

#include <stdbool.h>

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Atlas {
    char name[50];
    struct Atlas *next;
} Atlas;

Atlas* LoadAtlas(const char*);
void FreeAtlas(Atlas*);

void SetRegion(Atlas*, int x, int y, int w, int h, const char*);
void GetRegion(Atlas*, const char*);
bool HasRegion(Atlas*, const char*);

void BindAtlas(Atlas*);
void UnbindAtlas();

#ifdef __cplusplus
}
#endif

#endif
