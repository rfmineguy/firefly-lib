#include "../include/Resource/Geometry.h"
#include "../include/Rendering/Shapes.h"
#include "../include/Resource/ResourceManager.h"
#include <glad/glad.h>

static Geometry quad;

void InitShapes() {
    static bool init = false;
    if (!init) {
        PopulateQuad(&quad);
        init = true;
    }
}

void FreeShapes() {
    static bool free = false;
    if (!free) {
        FreeGeometry(&quad);
        free = true;
    }
}

void DrawQuad() {
    BindGeometry(&quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
