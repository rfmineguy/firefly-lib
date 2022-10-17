#ifndef FF_RESOURCE_FONT_H
#define FF_RESOURCE_FONT_H

#include "ft2build.h"
#include FT_FREETYPE_H
#include <stdint.h>

typedef struct {
  uint32_t texId;
  int size_w, size_h;
  int bearing_x, bearing_y;
  unsigned int advance;
  char c;
} FF_Char;

typedef struct {
  FF_Char characters[128];
  FT_Face face;
} FF_Font;

typedef struct FF_int_FontLoader {
  FT_Library ft_lib;
} FF_FontLoader;

FF_FontLoader* FF_CreateFontLoader();
void FF_DestroyFontLoader(FF_FontLoader*);

FF_Font FF_LoadFont(FF_FontLoader*, const char*);

#endif