#include "../include/Core/PerspectiveCamera.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"

void FF_PerspectiveCameraUpdateCameraVectors(Camera* pCamera) {
  vec3 front;
  Input* i = FF_int_GetInputPtr();
  front[0] = cos(glm_rad(i->yaw)) * cos(glm_rad(i->pitch));
  front[1] = sin(glm_rad(i->pitch));
  front[2] = sin(glm_rad(i->yaw)) * cos(glm_rad(i->pitch));
  
  glm_vec3_normalize_to(front, pCamera->camFront);
  
  vec3 crossFrontUp;
  glm_cross(pCamera->camFront, pCamera->up, crossFrontUp);
  glm_normalize_to(crossFrontUp, pCamera->camRight);
  
  vec3 crossRightFront;
  glm_cross(pCamera->camRight, pCamera->camFront, crossRightFront);
  glm_normalize_to(crossRightFront, pCamera->camUp);
}

void FF_PerspectiveCameraUpdateProj(Camera camera, int width, int height) {
  camera.size[0] = width;
  camera.size[1] = height;
  glm_perspective(glm_rad(camera.fov), camera.size[0] / camera.size[1], 0.1f, 100.0f, camera.proj);
}

Camera FF_PerpsectiveCamera() {
  Camera c;
  c.projection_type = PERSPECTIVE;
  c.fov = 45.f;
  glm_vec2_copy((vec2){600, 600}, c.size);
  glm_vec3_copy((vec3){0, 0, 20}, c.camPos);
  glm_vec3_copy((vec3){0, 0, 0}, c.camTarget);
  glm_vec3_copy((vec3){0, 1, 0}, c.up);
  glm_vec3_copy((vec3){0, 0, 0}, c.camRight);
  glm_vec3_copy((vec3){0, 1, 0}, c.camUp);
  glm_vec3_copy((vec3){0, 0, -1}, c.camFront);
  FF_PerspectiveCameraUpdateProj(c, 600, 600);
  return c;
}

void FF_PerspectiveCameraUpdate(Camera camera) {
  vec3 posPlusFront;
  glm_vec3_add(camera.camPos, camera.camFront, posPlusFront);
  glm_lookat(camera.camPos, posPlusFront, camera.up, camera.view);
  
  const float camSpeed = 0.05f;
  if (FF_IsKeyDown(KEY_W)) {
    LOG_DEBUG("Move forward");
    glm_vec3_muladds(camera.camFront, camSpeed, camera.camPos);  //?
  }
  if (FF_IsKeyDown(KEY_S)) {
    LOG_DEBUG("Move backward");
    glm_vec3_muladds(camera.camFront, -camSpeed, camera.camPos); //?
  }
  if (FF_IsKeyDown(KEY_A)) {
    LOG_DEBUG("Move left");
    vec3 cross;
    glm_vec3_cross(camera.camFront, camera.camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, -camSpeed, camera.camPos);
  }
  if (FF_IsKeyDown(KEY_D)) {
    LOG_DEBUG("Move right");
    vec3 cross;
    glm_vec3_cross(camera.camFront, camera.camUp, cross);
    glm_normalize(cross);
    glm_vec3_muladds(cross, camSpeed, camera.camPos);
  }
  
  FF_PerspectiveCameraUpdateCameraVectors(&camera);
  //LOG_DEBUG("cam_front_x: %0.4f, cam_front_y: %0.4f, cam_front_z: %0.4f", camera.camFront[0], camera.camFront[1], camera.camFront[2]);
  //LOG_DEBUG("cam_x: %0.4f, cam_y: %0.4f, cam_z: %0.4f", camera.camPos[0], camera.camPos[1], camera.camPos[2]);
}
