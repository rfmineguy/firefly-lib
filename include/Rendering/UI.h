#ifndef FL_REND_UI_H
#define FL_REND_UI_H

// Allows for c++ to link lib
#ifdef __cplusplus
extern "C" {
#endif

void BeginUI();
void EndUI();
void RenderUI();

void DrawButton();
void DrawText(const char*);
void DrawSwitch();

#ifdef __cplusplus
}
#endif

#endif
