#include "../include/Core/Input.h"
#include <stdio.h>

static Input gInput;

Input* GetInputPtr() {
    return &gInput;
}

bool IsKeyDown(int key) {
    return GetInputPtr()->keys[key].down;
}

bool IsKeyPressed(int key) {
    bool pressed = GetInputPtr()->keys[key].pressed;//IsKeyDown(key);
    GetInputPtr()->keys[key].pressed = false;
    return pressed && !GetInputPtr()->keys[key].repeat;
}

bool IsControlDown() {
    return IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
}

bool IsShiftDown() {
    return IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
}

bool IsAltDown() {
    return IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
}

bool IsMouseButtonDown(int button) {
    return GetInputPtr()->mouse_pressed && GetInputPtr()->mouse[button];
}

bool IsMouseButtonPressed(int button) {
    if (IsMouseButtonDown(button)) {
        GetInputPtr()->mouse_pressed = false;
        return true;
    }
    return false;
}

//may not be very useful
bool IsMouseMoving() {
    return GetInputPtr()->mouse_offset.x != 0 || GetInputPtr()->mouse_offset.y != 0;
}

Vec2f GetMousePosition() {
    return GetInputPtr()->mouse_pos;
}

double GetMousePositionX() {
    return GetInputPtr()->mouse_pos.x; 
}

double GetMousePositionY() {
    return GetInputPtr()->mouse_pos.y; 
}

Vec2f GetMouseSpeed() {
    return GetInputPtr()->mouse_offset;
}

double GetMouseSpeedX() {
    return GetInputPtr()->mouse_offset.x;
}

double GetMouseSpeedY() {
    return GetInputPtr()->mouse_offset.y;
}

double GetMouseYaw() {
    return GetInputPtr()->yaw;
}

double GetMousePitch() {
    return GetInputPtr()->pitch;
}

bool IsScroll() {
    return IsScrollUp() || IsScrollDown() || IsScrollRight() || IsScrollLeft();
}

bool IsScrollUp() {
    return GetInputPtr()->scroll_offset.y > 0.1;
}

bool IsScrollDown() {
    return GetInputPtr()->scroll_offset.y < -0.1;
}

bool IsScrollRight() {
    return GetInputPtr()->scroll_offset.x < -0.11;
}

bool IsScrollLeft() {
    return GetInputPtr()->scroll_offset.x > 0.11;
}

Vec2f GetScrollDirection() {
    float xDir = 0, yDir = 0;
    if (IsScrollDown()) yDir = -1;
    if (IsScrollUp()) yDir = 1;
    if (IsScrollRight()) xDir = 1;
    if (IsScrollLeft()) xDir = -1;
    return (Vec2f){.x=xDir, .y=yDir};
}
