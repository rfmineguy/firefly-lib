#include "../include/Rendering/Renderer.h"
#include "../include/IO/Log.h"
#include "../include/Resource/Shader.h"
#include <glad/glad.h>

extern char cam_frag[];
extern unsigned int cam_frag_len;
extern char cam_vert[];
extern unsigned int cam_vert_len;

static Shader* all_encompassing_shader = NULL;

void FF_InitRenderer() {
  //this will fail for the time being
  SetLogStream(stdout);
  LOG_INFO("[Renderer] Init");
  all_encompassing_shader = LoadShaderRaw(cam_vert, cam_vert_len, cam_frag, cam_frag_len);
}

void FF_DeinitRenderer() {
  FreeShader(all_encompassing_shader);
}

void FF_RendererDrawGeometry(Geometry g) {
  BindGeometry(&g);
  BindShader(all_encompassing_shader);
  glDrawElements(GL_TRIANGLES, g.indice_count, GL_UNSIGNED_INT, 0);
}

void FF_RendererDrawGeometryEx(Geometry g, Camera c, vec3 pos, vec3 scale, vec3 rotAxis, float angle) {
  mat4 transform;
  glm_mat4_identity(transform);
  glm_translate(transform, pos);
  glm_scale(transform, scale);
  glm_rotate(transform, glm_rad(angle), rotAxis);
  
  BindShader(all_encompassing_shader);
  SetUniform4fv(all_encompassing_shader, "view", c.view[0]);
  SetUniform4fv(all_encompassing_shader, "projection", c.proj[0]);

  SetUniform4fv(all_encompassing_shader, "model", transform[0]);
  BindGeometry(&g);
  
  glDrawElements(GL_TRIANGLES, g.indice_count, GL_UNSIGNED_INT, 0);
}
