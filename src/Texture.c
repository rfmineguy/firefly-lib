#include "../include/Resource/Texture.h"
#include "../include/IO/Log.h"
#include "../libs/stb/stb_image.h"
#include <stdlib.h>

Texture FF_LoadTexture(const char* path) {
  return FF_LoadTextureEx(path, GL_REPEAT, GL_NEAREST);
}

Texture FF_LoadTextureEx(const char* path, GLint wrap, GLint filter) {
  Texture t;
  glGenTextures(1, &t.handle);
  glBindTexture(GL_TEXTURE_2D, t.handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

  unsigned char* data = stbi_load(path, &t.width, &t.height, &t.channels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.width, t.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    LOG_INFO("Loaded texture [%s] [width:%d, height:%d, channels:%d]", path, t.width, t.height, t.channels);
  }
  else {
    LOG_CRITICAL("Failed to read file [%s]", path);
  }
  stbi_image_free(data);
  return t;
}

void FF_FreeTexture(Texture t) {
  FF_UnbindTexture(t);
  glDeleteTextures(1, &t.handle);
}

void FF_BindTexture(Texture t) {
  FF_BindTextureToUnit(t, 0);
}

void FF_BindTextureToUnit(Texture t, int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, t.handle);
}

void FF_UnbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}