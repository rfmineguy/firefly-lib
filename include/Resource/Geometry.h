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
    uint32_t vertex_count;
    uint32_t* indices;
    uint32_t indice_count;
} Geometry;

void BindGeometry(Geometry*);
void UnbindGeometry();
void FreeGeometry(Geometry);

Geometry GenerateQuad();
void GenerateCube(Geometry*);

#endif
