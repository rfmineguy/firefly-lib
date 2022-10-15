#include "../include/Rendering/Renderer.h"
#include "../include/IO/Log.h"
#include "../include/Resource/Shader.h"
#include <glad/glad.h>
#include <string.h>

extern char cam_frag[];
extern unsigned int cam_frag_len;
extern char cam_vert[];
extern unsigned int cam_vert_len;

typedef struct _Character {
  
} Character;

typedef struct int_FF_Renderer {
  Shader* camShader;
} FF_Renderer;

FF_Renderer* FF_CreateRenderer(FF_Window* windowPtr) {
  FF_Renderer* r = malloc(sizeof(*r));
  r->camShader = LoadShaderRaw(cam_vert, cam_vert_len, cam_frag, cam_frag_len);
  LOG_INFO("[Renderer] Created successfully");
  return r;
}

void FF_DestroyRenderer(FF_Renderer* rendererPtr) {
  FreeShader(rendererPtr->camShader);
  free(rendererPtr);
  rendererPtr = NULL;
  LOG_INFO("[Renderer] Destroyed successfully");
}

void FF_RendererDrawGeometry(FF_Renderer* r, Geometry g, Camera c, vec3 pos, vec3 scale, vec3 rotAx, float rot) {
  // Transformation matrix calculation
  mat4 transform;
  glm_mat4_identity(transform);
  glm_translate(transform, pos);
  glm_scale(transform, scale);
  glm_rotate(transform, glm_rad(rot), rotAx);
  
  // Binding
  BindShader(r->camShader);
  BindGeometry(&g);

  // Uniform data
  SetUniform4fv(r->camShader, "view", c.view[0]);
  SetUniform4fv(r->camShader, "projection", c.proj[0]);
  SetUniform4fv(r->camShader, "model", transform[0]);
  
  // Draw call
  glDrawElements(GL_TRIANGLES, g.indice_count, GL_UNSIGNED_INT, 0);
}