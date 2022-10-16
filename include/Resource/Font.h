#ifndef FF_RESOURCE_FONT_H
#define FF_RESOURCE_FONT_H

#include "ft2build.h"
#include FT_FREETYPE_H

typedef struct _Font {
  FT_Face face;
} Font;

void FF_InitFontSystem();
void FF_DeinitFontSystem();

Font FF_LoadFont(const char*);

#endif