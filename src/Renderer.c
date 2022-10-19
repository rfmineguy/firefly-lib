#include "../include/Rendering/Renderer.h"
#include "../include/IO/Log.h"
#include "../include/Resource/Shader.h"
#include <glad/glad.h>
#include <string.h>

extern char cam_frag[];
extern unsigned int cam_frag_len;
extern char cam_vert[];
extern unsigned int cam_vert_len;

extern char text_frag[]; extern unsigned int text_frag_len;
extern char text_vert[]; extern unsigned int text_vert_len;

typedef struct int_FF_Renderer {
  Shader *camShader, *textShader;
  unsigned int font_vao, font_vbo;
} FF_Renderer;

FF_Renderer* FF_CreateRenderer(FF_Window* windowPtr) {
  FF_Renderer* r = malloc(sizeof(*r));
  r->camShader = LoadShaderRaw(cam_vert, cam_vert_len, cam_frag, cam_frag_len);
  r->textShader = LoadShaderRaw(text_vert, text_vert_len, text_frag, text_frag_len);
  
  glGenVertexArrays(1, &r->font_vao);
  glGenBuffers(1, &r->font_vbo);
  glBindVertexArray(r->font_vao);
  glBindBuffer(GL_ARRAY_BUFFER, r->font_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  LOG_INFO("[Renderer] Created successfully");
  return r;
}

void FF_DestroyRenderer(FF_Renderer* rendererPtr) {
  FreeShader(rendererPtr->camShader);
  FreeShader(rendererPtr->textShader);
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

void FF_RendererDrawText(FF_Renderer* r, FF_Font fnt, Camera c, vec2 pos, vec3 color, float scale, const char* fmt, ...) {
  char str[500];
  va_list args;
  va_start(args, fmt);
  vsprintf(str, fmt, args);
  va_end(args);
  
  mat4 proj;
  glm_mat4_identity(proj);
  glm_ortho(0, c.size[0], 0, c.size[1], -100, 100, proj);
  
  BindShader(r->textShader);
  SetUniform3f(r->textShader, "textColor", color[0], color[1], color[2]);
  SetUniform4fv(r->textShader, "projection", proj[0]);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(r->font_vao);
  
  for (int i = 0; i < strlen(str); i++) {
    FF_Char c = fnt.characters[(int)str[i]];
    float xpos = pos[0] + c.bearing_x * scale;
    float ypos = pos[1] - (c.size_h - c.bearing_y) * scale;
    float w = c.size_w * scale;
    float h = c.size_h * scale;
    
    float vertices[6][4] = {
       { xpos,     ypos + h,   0.0f, 0.0f },            
       { xpos,     ypos,       0.0f, 1.0f },
       { xpos + w, ypos,       1.0f, 1.0f },

       { xpos,     ypos + h,   0.0f, 0.0f },
       { xpos + w, ypos,       1.0f, 1.0f },
       { xpos + w, ypos + h,   1.0f, 0.0f }
    };
    
    glBindTexture(GL_TEXTURE_2D, c.texId);
    glBindBuffer(GL_ARRAY_BUFFER, r->font_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    pos[0] += (c.advance >> 6) * scale;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
