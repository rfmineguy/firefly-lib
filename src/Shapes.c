#include "../include/Resource/Geometry.h"
#include "../include/Rendering/Shapes.h"
#include "../include/Resource/ResourceManager.h"
#include <glad/glad.h>

static Geometry quad, cube;
static Shader* camShader;

void InitShapes() {
//    static bool init = false;
//    if (!init) {
//        GenerateQuad(&quad);
//        GenerateCube(&cube);
//        camShader = LoadShader("res/shader/", "camera");
//        init = true;
//    }
}

void FreeShapes() {
//    static bool free = false;
//    if (!free) {
//        FreeGeometry(&quad);
//        FreeGeometry(&cube);
//        FreeShader(camShader);
//        free = true;
//    }
}

void DrawQuad() {
    BindGeometry(&quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawCube() {
    BindGeometry(&cube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void DrawCubeEx(vec3 pos, vec3 scale, vec3 rotAxis, float angle, Camera* pCamera) {
    BindShader(camShader);
    
    mat4 transform;
    glm_mat4_identity(transform);
    glm_translate(transform, pos);
    glm_scale(transform, scale);
    glm_rotate(transform, glm_rad(angle), rotAxis);

    SetUniform4fv(camShader, "view", pCamera->view[0]);
    SetUniform4fv(camShader, "projection", pCamera->proj[0]);

    SetUniform4fv(camShader, "model", transform[0]);

    BindGeometry(&cube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
