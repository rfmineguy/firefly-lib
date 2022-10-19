#ifndef FF_RENDERING_RECT_H
#define FF_RENDERING_RECT_H

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  float x, y, w, h;
} FF_Rect;

#ifdef __cplusplus
}
#endif

#endif