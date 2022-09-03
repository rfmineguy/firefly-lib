#include "../include/Resource/Texture.h"
#include "../include/IO/Log.h"
#include "glad/glad.h"
#include "../libs/stb/stb_image.h"
#include <stdlib.h>

Texture* LoadTexture(const char* path) {
  Texture *t = malloc(sizeof(*t));
  glGenTextures(1, &t->handle);
  glBindTexture(GL_TEXTURE_2D, t->handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned char* data = stbi_load(path, &t->width, &t->height, &t->channels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    LOG_INFO("Loaded texture [%s] [width:%d, height:%d, channels:%d]", path, t->width, t->height, t->channels);
  }
  else {
    LOG_CRITICAL("Failed to read file [%s]", path);
  }
  stbi_image_free(data);
  return t;
}

void FreeTexture(Texture *pTexture) {
  UnbindTexture(pTexture);
  glDeleteTextures(1, &pTexture->handle);
}

void BindTexture(Texture *pTexture) {
  glBindTexture(GL_TEXTURE_2D, pTexture->handle);
}

void BindTextureToUnit(Texture *pTexture, int unit) {
  BindTexture(pTexture);
}

void UnbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
