#include "../include/Core/Input.h"
#include <stdio.h>

static Input gInput;

Input* GetInputPtr() {
    return &gInput;
}

bool IsKeyDown(int key) {
    return GetInputPtr()->key_pressed && GetInputPtr()->keys[key];
}

bool IsKeyPressed(int key) {
    if (IsKeyDown(key)) {
        GetInputPtr()->key_pressed = false;
        return true;
    }
    return false;
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