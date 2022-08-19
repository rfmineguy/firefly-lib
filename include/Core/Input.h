#ifndef FL_COREINPUT_H
#define FL_COREINPUT_H
#include "Vec.h"
#include <stdbool.h>

typedef struct _KeyBind KeyBind;
typedef struct {
    bool keys[500];
    bool mouse[12];
    bool repeat;
    Vec2f mouse_pos;
    Vec2f mouse_velocity;
} Input;

Input* GetInputPtr();

//Input device functions (Input.h)
void KeyBindRegister(const char*, int, int);
void KeyBindModify(const char*, int, int);
bool IsKeyBindDown(const char*);
bool IsKeyBindPressed(const char*);

bool IsKeyDown(int);
bool IsControlDown();
bool IsAltDown();
bool IsShiftDown();
bool IsKeyPressed(int);

bool IsMouseButtonDown(int);
bool IsMouseButtonPressed(int);
bool IsMouseMoving();
Vec2f GetMousePosition();
float GetMousePositionX();
float GetMousePositionY();
Vec2f GetMouseSpeed();
float GetMouseSpeedX();
float GetMouseSpeedY();

//FUTURE
bool IsControllerConneced(int);
bool IsControllerButtonDown(int, int);
bool IsControllerButtonPressed(int, int);

#endif
