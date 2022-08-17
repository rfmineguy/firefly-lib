#ifndef FL_RES_ATLAS_H
#define FL_RES_ATLAS_H

typedef struct {

} Atlas;

Atlas* LoadAtlas(const char*);
void FreeAtlas(Atlas*);

void SetRegion(Atlas*, int x, int y, int w, int h, const char*);
void GetRegion(Atlas*, const char*);
bool HasRegion(Atlas*, const char*);

void BindAtlas(Atlas*);
void UnbindAtlas();
#endif
