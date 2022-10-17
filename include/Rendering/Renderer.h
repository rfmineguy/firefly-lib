#ifndef FF_RENDERING_RENDERER_H
#define FF_RENDERING_RENDERER_H
#include "../Resource/Geometry.h"
#include "../Resource/Font.h"
#include "../Core/Camera.h"
#include "../Core/Window.h"

typedef struct int_FF_Renderer FF_Renderer;

FF_Renderer* FF_CreateRenderer(FF_Window*);
void FF_DestroyRenderer(FF_Renderer*);

void FF_RendererDrawGeometry(FF_Renderer*, Geometry, Camera, vec3, vec3, vec3, float);
void FF_RendererDrawText(FF_Renderer*, FF_Font, Camera, vec2, vec3, float, const char*, ...);

#endif