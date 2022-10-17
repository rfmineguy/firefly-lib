#include "ft2build.h"
#include FT_FREETYPE_H

#include "../include/Resource/Font.h"
#include "../include/IO/IO.h"

FT_Library library;

typedef struct _FF_Font {
  FT_Face face;
} FF_Font;

void FF_InitFontSystem() {
  FT_Error e = FT_Init_FreeType(&library);
  if (e) {
    LOG_CRITICAL("Error initializing freetype");
  }
  else {
    LOG_INFO("[FontSystem] Initialized font system");
  }
}

void FF_DeinitFontSystem() {
  LOG_INFO("[FontSystem] Deinitialized font system");
}

FF_Font FF_LoadFont(const char* path) {
  FF_Font f;
  FT_Error e = FT_New_Face(library, path, 0, &f.face);
  if (e == FT_Err_Unknown_File_Format) {
    LOG_CRITICAL("Font format not recongnized, [%s]", path);
    return (FF_Font){};
  }
  else if (e) {
    LOG_CRITICAL("Unknown problem with font file, [%s]", path);
    return (FF_Font){};
  }
  LOG_INFO("Loaded font at [%s]", path);
  return f;
}