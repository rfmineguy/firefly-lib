#include "../include/Resource/Texture.h"
#include "../include/IO/Log.h"
#include "../libs/stb/stb_image.h"
#include <stdlib.h>

Texture* LoadTexture(const char* path) {
  return LoadTextureEx(path, GL_REPEAT, GL_NEAREST);
}

Texture* LoadTextureEx(const char *path, GLint wrapValue, GLint filterValue) {
  Texture *t = malloc(sizeof(*t));
  glGenTextures(1, &t->handle);
  glBindTexture(GL_TEXTURE_2D, t->handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapValue);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapValue);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterValue);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterValue);

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
  BindTextureToUnit(pTexture, 0);
}

void BindTextureToUnit(Texture *pTexture, int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, pTexture->handle);
  //BindTexture(pTexture);
}

void UnbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
