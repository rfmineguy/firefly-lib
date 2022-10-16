#include "../include/Resource/Font.h"
#include "../include/IO/IO.h"

void FF_FreeTypeInit() {
  FT_Error e = FT_Init_FreeType(&library);
  if (e) {
    LOG_CRITICAL("Error initializing freetype");
  }
}

Font FF_LoadFont(const char* path) {
  return (Font){};
}