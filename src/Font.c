#include "../include/Resource/Font.h"
#include "../include/IO/IO.h"
#include <glad/glad.h>

FT_Library library;

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
  FT_Done_FreeType(library);
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
  else {
    LOG_INFO("Loaded font at [%s]", path);
    FT_Set_Pixel_Sizes(f.face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (int c = 0; c < 128; c++) {
      if ((e = FT_Load_Char(f.face, c, FT_LOAD_RENDER)) != 0) {
        LOG_CRITICAL("Failed to load font glyph [%c]", c);
        continue;
      }
      FF_Char char_struct;
      glGenTextures(1, &char_struct.texId);
      glBindTexture(GL_TEXTURE_2D, char_struct.texId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, f.face->glyph->bitmap.width, f.face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, f.face->glyph->bitmap.buffer);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
      char_struct.size_w = f.face->glyph->bitmap.width;
      char_struct.size_h = f.face->glyph->bitmap.rows;
      char_struct.bearing_x = f.face->glyph->bitmap_left;
      char_struct.bearing_y = f.face->glyph->bitmap_top;
      f.characters[c] = char_struct;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  FT_Done_Face(f.face);
  return f;
}