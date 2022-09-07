#ifndef FL_REND_SHAPES_H
#define FL_REND_SHAPES_H
#include "../Core/Vec.h"
#include "../Core/Camera.h"

void InitShapes();
void FreeShapes();

void BeginDraw(Camera*);
void EndDraw();

void DrawQuad();

void DrawCube();
void DrawCubeEx(vec3, vec3, vec3, float, Camera*);

void DrawCircle(Vec2f, float);
void DrawPoly(Vec2f*, int);
void DrawLine(Vec2f, Vec2f);

#endif
