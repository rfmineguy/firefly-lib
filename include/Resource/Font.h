#ifndef FF_RESOURCE_FONT_H
#define FF_RESOURCE_FONT_H

#include "ft2build.h"
#include FT_FREETYPE_H

typedef struct _Font {

} Font;

FT_Library library;

void FF_FreeTypeInit();
Font FF_LoadFont(const char*);


#endif