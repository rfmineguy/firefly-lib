#ifndef FL_COREWINDOW_H
#define FL_COREWINDOW_H
#include "Timer.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    OPENGL, VULKAN, METAL
} API;
typedef struct _Window Window;

API FF_DetectAPI();
void FF_InitWindow();
void FF_InitWindowEx(const char*, int, int);
void FF_InitWindowAPI(API);
void FF_InitWindowAPIEx(API, const char*, int, int);
void FF_InitWindowGL();
void FF_InitWindowGLEx(const char*, int, int);
void FF_InitWindowVK();
void FF_InitWindowVKEx(const char*, int, int);
void FF_InitWindowMTL();
void FF_InitWindowMTLEx(const char*, int, int);

Window* FF_CreateWindowGL(const char*, uint16_t, uint16_t);
void FF_DestroyWindowGL(Window*);

void FF_DestroyWindow();
void FF_DestroyWindowAPI(API);
void FF_DestroyWindowGL();
void FF_DestroyWindowVK();
void FF_DestroyWindowMetal();

void FF_WindowClearBackground(Window*);
void FF_WindowClearBackgroundEx(Window*, float, float, float, float);
void FF_WindowSetFPSCap(Window*, float);
void FF_WindowSetVSync(Window*);
bool FF_WindowShouldClose(Window*);
void FF_SetWindowShouldClose(Window*, bool);
void FF_SetWindowCloseKey(Window*, int);
void FF_WindowPollEvents(Window*);
double FF_GetTime();
double FF_WindowDeltaTime(Window*);
void FF_WindowMinimize(Window*);
bool FF_IsWindowMinimized(Window*);
void FF_WindowSetFullscreen(Window*, bool);
void FF_WindowToggleFullscreen(Window*);
bool FF_IsWindowFullscreen(Window*);
bool FF_WasWindowResized(Window*);
int FF_WindowGetWidth(Window*);
int FF_WindowGetHeight(Window*);

void FF_ToggleCursorLocked(Window*);
bool FF_IsCursorLocked(Window*);

#endif
