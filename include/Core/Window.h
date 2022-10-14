#ifndef FL_COREWINDOW_H
#define FL_COREWINDOW_H
#include "Timer.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    OPENGL, VULKAN, METAL
} API;
typedef struct _FF_Window FF_Window;

FF_Window* FF_CreateWindowGL(const char*, uint16_t, uint16_t, bool);
void FF_DestroyWindowGL(FF_Window*);

void FF_WindowClearBackground(FF_Window*);
void FF_WindowClearBackgroundEx(FF_Window*, float, float, float, float);
void FF_WindowSetFPSCap(FF_Window*, float);
void FF_WindowSetVSync(FF_Window*);
bool FF_WindowShouldClose(FF_Window*);
void FF_SetWindowShouldClose(FF_Window*, bool);
void FF_WindowCloseKey(FF_Window*, int);
void FF_WindowPollEvents(FF_Window*);
double FF_GetTime();
double FF_WindowDeltaTime(FF_Window*);
void FF_WindowMinimize(FF_Window*);
bool FF_WindowMinimized(FF_Window*);
void FF_WindowSetFullscreen(FF_Window*, bool);
void FF_WindowToggleFullscreen(FF_Window*);
bool FF_WindowFullscreen(FF_Window*);
bool FF_WindowResized(FF_Window*);
int FF_WindowGetWidth(FF_Window*);
int FF_WindowGetHeight(FF_Window*);

void FF_ToggleCursorLocked(FF_Window*);
bool FF_IsCursorLocked(FF_Window*);

#endif
