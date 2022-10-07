#include "../include/Core/OrthoCamera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"

void RecalcView(Camera* pCamera) {
  mat4 transform;
  glm_mat4_identity(transform);
  glm_translate(transform, pCamera->camPos);
  glm_rotate(transform, 0, (vec3){0, 0, 1});
  glm_mat4_inv(transform, pCamera->view);
}

Camera FF_OrthoCamera() {
  Camera c;
  c.projection_type = ORTHOGRAPHIC;
  glm_vec3_copy((vec3){0, 0, 0}, c.camPos);
  glm_mat4_identity(c.view);
  return c;
}

void FF_OrthoCameraUpdate(Camera* pCamera) {
  const float camSpeed = 0.05f;
  if (FF_IsKeyDown(KEY_W)) {
    pCamera->camPos[1] -= camSpeed;
  }
  if (FF_IsKeyDown(KEY_S)) {
    pCamera->camPos[1] += camSpeed;
  }
  if (FF_IsKeyDown(KEY_A)) {
    pCamera->camPos[0] -= camSpeed;
  }
  if (FF_IsKeyDown(KEY_D)) {
    pCamera->camPos[0] += camSpeed;
  }
  
}

void FF_OrthoCameraUpdateProj(Camera* pCamera, int width, int height) {
  pCamera->size[0] = width;
  pCamera->size[1] = height;
  //glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f, proj);
  glm_ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f, 1.0f, pCamera->proj);
}
