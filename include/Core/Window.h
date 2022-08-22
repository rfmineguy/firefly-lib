#ifndef FL_COREWINDOW_H
#define FL_COREWINDOW_H
#include "Timer.h"
#include <stdbool.h>

typedef enum {
    OPENGL, VULKAN, METAL
} API;
typedef struct _Window Window;

API DetectAPI();
void InitWindow();
void InitWindowEx(const char*, int, int);
void InitWindowAPI(API);
void InitWindowAPIEx(API, const char*, int, int);
void InitWindowGL();
void InitWindowGLEx(const char*, int, int);
void InitWindowVK();
void InitWindowVKEx(const char*, int, int);
void InitWindowMTL();
void InitWindowMTLEx(const char*, int, int);

void DestroyWindow();
void DestroyWindowAPI(API);
void DestroyWindowGL();
void DestroyWindowVK();
void DestroyWindowMetal();

void WindowClearBackground();
void WindowClearBackgroundEx(float, float, float, float);
void WindowSetFPSCap(float);
void WindowSetVSync();
bool WindowShouldClose();
void SetWindowShouldClose(bool);
void SetWindowCloseKey(int);
void WindowPollEvents();
double WindowDeltaTime();
void WindowMinimize();
bool IsWindowMinimized();
void WindowSetFullscreen(bool);
void WindowToggleFullscreen();
bool IsWindowFullscreen();

#endif
