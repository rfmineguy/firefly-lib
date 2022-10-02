#ifndef FF_RENDERING_RENDERER_H
#define FF_RENDERING_RENDERER_H
#include "../Resource/Geometry.h"
#include "../Core/Camera.h"

void FF_InitRenderer();
void FF_DeinitRenderer();

void FF_RendererDrawGeometry(Geometry);
void FF_RendererDrawGeometryEx(Geometry, Camera, vec3, vec3, vec3, float);

#endif