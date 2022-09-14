#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <stdio.h>
#include <stdlib.h>

static Input gInput;// = {.keybinds=ht_create() };

Input* GetInputPtr() {
    return &gInput;
}

void InitKeybindHT() {
    static bool initialized = false;
    if (!initialized) {
        GetInputPtr()->keybinds = ht_create();
        initialized = true;
    }
}

void DeinitKeybindHT() {
    ht_free(GetInputPtr()->keybinds);
}

void KeyBindRegister(const char* name, int primary_key, int secondary_key) {
    if (ht_get(GetInputPtr()->keybinds, name) != NULL)
        return;
    KeyBind* k = malloc(sizeof(KeyBind));
    k->primary = primary_key;
    k->secondary = secondary_key;
    ht_set(GetInputPtr()->keybinds, name, k);
}

void KeyBindModify(const char* name, int new_primary_key, int new_secondary_key) {
    KeyBind* k = ht_get(GetInputPtr()->keybinds, name);
    if (k == NULL) {
        return;
    }
    k->primary = new_primary_key;
    k->secondary = new_secondary_key;
}

bool IsKeyBindDown(const char* name) {
    KeyBind* k = ht_get(GetInputPtr()->keybinds, name);
    if (k == NULL) {
        LOG_CRITICAL("Keybind [%s] not registered", name);
        return false;
    }
    return (k->primary != KEY_NONE && IsKeyDown(k->primary)) || (k->secondary != KEY_NONE && IsKeyDown(k->secondary));
}

bool IsKeyBindPressed(const char* name) {
    KeyBind* k = ht_get(GetInputPtr()->keybinds, name);
    if (k == NULL) {
        LOG_CRITICAL("Keybind [%s] not registered", name);
        return false;
    }
    bool primary_pressed = k->primary != KEY_NONE && IsKeyPressed(k->primary);
    bool secondary_pressed = k->secondary != KEY_NONE && IsKeyPressed(k->secondary);
    return primary_pressed || secondary_pressed;
    //return (k->primary != KEY_NONE && IsKeyPressed(k->primary)) || (k->secondary != KEY_NONE && IsKeyPressed(k->secondary));
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
