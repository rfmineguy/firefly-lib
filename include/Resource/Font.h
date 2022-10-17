#ifndef FF_RESOURCE_FONT_H
#define FF_RESOURCE_FONT_H
#include "ft2build.h"
#include FT_FREETYPE_H
typedef struct {
  uint32_t texId;
  int size_w, size_h;
  int bearing_x, bearing_y;
  uint32_t advance;
} FF_Char;

typedef struct {
  FF_Char characters[128];
  FT_Face face;
} FF_Font;

void FF_InitFontSystem();
void FF_DeinitFontSystem();

FF_Font FF_LoadFont(const char*);

#endif