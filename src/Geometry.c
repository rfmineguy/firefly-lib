#include "../include/Resource/Geometry.h"
#include <stdint.h>
#include "../libs/glad-rf/include/glad/glad.h"
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

    pGeometry->vertices[0] = (Vertex){ .position={ 0.5f,  0.5f, 0.0f}, .color={1.f, 1.f, 1.f}, .tex_coord={1.0f, 1.0f} };
    pGeometry->vertices[1] = (Vertex){ .position={ 0.5f, -0.5f, 0.0f}, .color={1.f, 1.f, 1.f}, .tex_coord={1.0f, 0.0f} };
    pGeometry->vertices[2] = (Vertex){ .position={-0.5f, -0.5f, 0.0f}, .color={1.f, 1.f, 1.f}, .tex_coord={0.0f, 0.0f} };
    pGeometry->vertices[3] = (Vertex){ .position={-0.5f,  0.5f, 0.0f}, .color={1.f, 1.f, 1.f}, .tex_coord={0.0f, 1.0f} };

    memcpy(pGeometry->indices, (uint32_t[]){0, 1, 3, 1, 2, 3}, sizeof(uint32_t) * 6);
    glGenVertexArrays(1, &pGeometry->vao);
    glGenBuffers(1, &pGeometry->vbo);
    glGenBuffers(1, &pGeometry->ebo);

    glBindVertexArray(pGeometry->vao);
    glBindBuffer(GL_ARRAY_BUFFER, pGeometry->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, pGeometry->vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pGeometry->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, pGeometry->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tex_coord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PopulateCube(Geometry* pGeometry) {
    pGeometry->vertices = (Vertex*) malloc(sizeof(Vertex) * 8);
    pGeometry->indices = (uint32_t*) malloc(sizeof(uint32_t) * 36);

    pGeometry->vertices[0] = (Vertex){.position={-1, -1, 0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={1.0f, 1.0f}};
    pGeometry->vertices[1] = (Vertex){.position={ 1, -1, 0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={1.0f, 0.0f}};
    pGeometry->vertices[2] = (Vertex){.position={-1,  1, 0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={0.0f, 0.0f}};
    pGeometry->vertices[3] = (Vertex){.position={ 1,  1, 0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={0.0f, 0.0f}};
    pGeometry->vertices[4] = (Vertex){.position={-1, -1, -0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={1.0f, 1.0f}};
    pGeometry->vertices[5] = (Vertex){.position={ 1, -1, -0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={1.0f, 0.0f}};
    pGeometry->vertices[6] = (Vertex){.position={-1,  1, -0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={0.0f, 1.0f}};
    pGeometry->vertices[7] = (Vertex){.position={ 1,  1, -0.5}, .color={1.f, 1.f, 1.f}, .tex_coord={0.0f, 0.0f}};

    memcpy(pGeometry->indices + 0, (uint32_t[]){2, 6, 7, 2, 3, 7}, sizeof(uint32_t) * 6);     //top
    memcpy(pGeometry->indices + 6, (uint32_t[]){0, 4, 5, 0, 1, 5}, sizeof(uint32_t) * 6);     //bottom
    memcpy(pGeometry->indices + 12, (uint32_t[]){0, 2, 6, 0, 4, 6}, sizeof(uint32_t) * 6);    //left
    memcpy(pGeometry->indices + 18, (uint32_t[]){1, 3, 7, 1, 5, 7}, sizeof(uint32_t) * 6);    //right
    memcpy(pGeometry->indices + 24, (uint32_t[]){0, 2, 3, 0, 1, 3}, sizeof(uint32_t) * 6);    //front
    memcpy(pGeometry->indices + 30, (uint32_t[]){4, 6, 7, 4, 5, 7}, sizeof(uint32_t) * 6);    //back

    glGenVertexArrays(1, &pGeometry->vao);
    glGenBuffers(1, &pGeometry->vbo);
    glGenBuffers(1, &pGeometry->ebo);

    glBindVertexArray(pGeometry->vao);
    glBindBuffer(GL_ARRAY_BUFFER, pGeometry->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, pGeometry->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pGeometry->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 36, pGeometry->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tex_coord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void FreeGeometry(Geometry* pGeometry) {
    free(pGeometry->vertices);
    pGeometry->vertices = NULL;
    free(pGeometry->indices);
    pGeometry->indices = NULL;
}