#ifndef FF_RENDERING_RENDERER_H
#define FF_RENDERING_RENDERER_H
#include "../Resource/Geometry.h"
#include "../Resource/Font.h"
#include "../Core/Camera.h"
#include "../Core/Window.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct int_FF_Renderer FF_Renderer;

/*
  DOCUMENTATION
  - Function: FF_CreateRenderer
  - Description: Creates and sets up the renderer's data
      -> shaders
      -> font data
  - Return: N/A
*/
FF_Renderer* FF_CreateRenderer(FF_Window*);

/*
  DOCUMENTATION
  - Function: FF_DestroyRenderer
  - Description: Destroys and frees loaded shaders and the renderer
  - Params: renderer
  - Return: N/A
*/
void FF_DestroyRenderer(FF_Renderer*);

/*
  DOCUMENTATION
  - Function: FF_RendererDrawGeometry
  - Description: Renders the given geometry depending on the arguments given
  - Params: renderer, geometry, cam, pos, scale, rotationAxis, rotation
  - Return: N/A
*/
void FF_RendererDrawGeometry(FF_Renderer*, Geometry, Camera, vec3, vec3, vec3, float);

/*
  DOCUMENTATION
  - Function: FF_RenderDrawText
  - Description: Renders the given text depending on the arguments given
  - Params: renderer, font, cam, pos, color, scale, fmt_str, str_args
  - Return: N/A
*/
void FF_RendererDrawText(FF_Renderer*, FF_Font, Camera, vec2, vec3, float, const char*, ...);


#ifdef __cplusplus
}
#endif

#endif