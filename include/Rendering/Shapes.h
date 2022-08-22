#ifndef FL_REND_SHAPES_H
#define FL_REND_SHAPES_H
#include "../Core/Vec.h"

void InitShapes();
void FreeShapes();

void DrawQuad();
void DrawCircle(Vec2f, float);
void DrawPoly(Vec2f*, int);
void DrawLine(Vec2f, Vec2f);

#endif
