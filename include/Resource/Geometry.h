#ifndef FL_RES_GEOMETRY_H
#define FL_RES_GEOMETRY_H
#include <cglm/cglm.h>

typedef struct _Vertex {
    vec3 position;
    vec3 color;
    vec2 tex_coord;
} Vertex;

typedef struct _Geometry {
    unsigned int vao, ebo, vbo;
    Vertex* vertices;
    uint32_t* indices;
} Geometry;

void BindGeometry(Geometry*);
void UnbindGeometry();
void FreeGeometry(Geometry*);

void PopulateQuad(Geometry*);

#endif
