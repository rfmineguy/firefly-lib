#ifndef FL_COREVEC_H
#define FL_COREVEC_H
#include <glad/glad.h>

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x, y;
} Vec2f;

typedef struct {
    double x, y, z;
} Vec3f;

#ifdef __cplusplus
}
#endif

#endif
