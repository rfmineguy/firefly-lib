#include "../include/Resource/Geometry.h"
#include <_types/_uint32_t.h>
#include <stdint.h>
#include <glad/glad.h>
#include <string.h>

void BindGeometry(Geometry* pGeometry) {
    glBindVertexArray(pGeometry->vao);
}

void UnbindGeometry() {
    glBindVertexArray(0);
}

void PopulateQuad(Geometry* pGeometry) {
    pGeometry->vertices = (Vertex*) malloc(sizeof(Vertex) * 4);
    pGeometry->indices = (uint32_t*) malloc(sizeof(uint32_t) * 6);

    pGeometry->vertices[0] = (Vertex){ .position={ 0.5f,  0.5f, 0.0f} };
    pGeometry->vertices[1] = (Vertex){ .position={ 0.5f, -0.5f, 0.0f} };
    pGeometry->vertices[2] = (Vertex){ .position={-0.5f, -0.5f, 0.0f} };
    pGeometry->vertices[3] = (Vertex){ .position={-0.5f,  0.5f, 0.0f} };

    //pGeometry->indices = (uint32_t[]){0, 1, 3, 1, 2, 3};
    memcpy(pGeometry->indices, (uint32_t[]){0, 1, 3, 1, 2, 3}, sizeof(uint32_t) * 6);
    glGenVertexArrays(1, &pGeometry->vao);
    glGenBuffers(1, &pGeometry->vbo);
    glGenBuffers(1, &pGeometry->ebo);

    glBindVertexArray(pGeometry->vao);
    glBindBuffer(GL_ARRAY_BUFFER, pGeometry->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, pGeometry->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pGeometry->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, pGeometry->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    printf("Initialized quad\n");
}

void FreeGeometry(Geometry* pGeometry) {
    printf("Free'd geometry [%p, %p]\n", pGeometry->vertices, pGeometry->indices);
    free(pGeometry->vertices);
    pGeometry->vertices = NULL;
    free(pGeometry->indices);
    pGeometry->indices = NULL;
}
