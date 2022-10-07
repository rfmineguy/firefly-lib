#include "../include/Core/OrthoCamera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"

void RecalcView(Camera* pCamera) {
  mat4 transform;
  glm_mat4_identity(transform);
  glm_translate(transform, pCamera->camPos);
  //glm_rotate(transform, 0, (vec3){0, 0, 1});
  glm_mat4_inv(transform, pCamera->view);
}

Camera FF_OrthoCamera() {
  Camera c;
  c.projection_type = ORTHOGRAPHIC;
  glm_vec3_copy((vec3){0, 0, 1}, c.camPos);
  glm_mat4_identity(c.view);
  FF_OrthoCameraUpdateProj(&c, 600, 600);
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
  RecalcView(pCamera);
  LOG_INFO("camPos: x=%0.4f y=%0.4f z=%0.4f", pCamera->camPos[0], pCamera->camPos[1], pCamera->camPos[2]);
  LOG_INFO("view: %0.4f %0.4f %0.4f %0.4f", pCamera->view[0][0], pCamera->view[0][1],pCamera->view[0][2],pCamera->view[0][3]);
  LOG_INFO("view: %0.4f %0.4f %0.4f %0.4f", pCamera->view[1][0], pCamera->view[1][1],pCamera->view[1][2],pCamera->view[1][3]);
  LOG_INFO("view: %0.4f %0.4f %0.4f %0.4f", pCamera->view[2][0], pCamera->view[2][1],pCamera->view[2][2],pCamera->view[2][3]);
  LOG_INFO("view: %0.4f %0.4f %0.4f %0.4f", pCamera->view[3][0], pCamera->view[3][1],pCamera->view[3][2],pCamera->view[3][3]);

  LOG_INFO("proj: %0.4f %0.4f %0.4f %0.4f", pCamera->proj[0][0], pCamera->proj[0][1],pCamera->proj[0][2],pCamera->proj[0][3]);
  LOG_INFO("proj: %0.4f %0.4f %0.4f %0.4f", pCamera->proj[1][0], pCamera->proj[1][1],pCamera->proj[1][2],pCamera->proj[1][3]);
  LOG_INFO("proj: %0.4f %0.4f %0.4f %0.4f", pCamera->proj[2][0], pCamera->proj[2][1],pCamera->proj[2][2],pCamera->proj[2][3]);
  LOG_INFO("proj: %0.4f %0.4f %0.4f %0.4f", pCamera->proj[3][0], pCamera->proj[3][1],pCamera->proj[3][2],pCamera->proj[3][3]);

}

void FF_OrthoCameraUpdateProj(Camera* pCamera, int width, int height) {
  pCamera->size[0] = width;
  pCamera->size[1] = height;
  glm_ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f, 1.0f, pCamera->proj);
}
