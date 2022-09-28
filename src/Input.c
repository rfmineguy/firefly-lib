#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <stdio.h>
#include <stdlib.h>

static Input gInput;// = {.keybinds=ht_create() };

Input* FF_int_GetInputPtr() {
    return &gInput;
}

void FF_InitKeybindHT() {
    static bool initialized = false;
    if (!initialized) {
        FF_int_GetInputPtr()->keybinds = ht_create();
        initialized = true;
    }
}

void FF_DeinitKeybindHT() {
    ht_free(FF_int_GetInputPtr()->keybinds);
}

void FF_KeyBindRegister(const char* name, int primary_key, int secondary_key) {
    if (ht_get(FF_int_GetInputPtr()->keybinds, name) != NULL)
        return;
    KeyBind* k = malloc(sizeof(KeyBind));
    k->primary = primary_key;
    k->secondary = secondary_key;
    ht_set(FF_int_GetInputPtr()->keybinds, name, k);
}

void FF_KeyBindModify(const char* name, int new_primary_key, int new_secondary_key) {
    KeyBind* k = ht_get(FF_int_GetInputPtr()->keybinds, name);
    if (k == NULL) {
        return;
    }
    k->primary = new_primary_key;
    k->secondary = new_secondary_key;
}

bool FF_IsKeyBindDown(const char* name) {
    KeyBind* k = ht_get(FF_int_GetInputPtr()->keybinds, name);
    if (k == NULL) {
        LOG_CRITICAL("Keybind [%s] not registered", name);
        return false;
    }
    return (k->primary != KEY_NONE && FF_IsKeyDown(k->primary)) || (k->secondary != KEY_NONE && FF_IsKeyDown(k->secondary));
}

bool FF_IsKeyBindPressed(const char* name) {
    KeyBind* k = ht_get(FF_int_GetInputPtr()->keybinds, name);
    if (k == NULL) {
        LOG_CRITICAL("Keybind [%s] not registered", name);
        return false;
    }
    bool primary_pressed = k->primary != KEY_NONE && FF_IsKeyPressed(k->primary);
    bool secondary_pressed = k->secondary != KEY_NONE && FF_IsKeyPressed(k->secondary);
    return primary_pressed || secondary_pressed;
    //return (k->primary != KEY_NONE && IsKeyPressed(k->primary)) || (k->secondary != KEY_NONE && IsKeyPressed(k->secondary));
}

bool FF_IsKeyDown(int key) {
    return FF_int_GetInputPtr()->keys[key].down;
}

bool FF_IsKeyPressed(int key) {
    bool pressed = FF_int_GetInputPtr()->keys[key].pressed;//IsKeyDown(key);
    FF_int_GetInputPtr()->keys[key].pressed = false;
    return pressed && !FF_int_GetInputPtr()->keys[key].repeat;
}

bool FF_IsControlDown() {
    return FF_IsKeyDown(KEY_LEFT_CONTROL) || FF_IsKeyDown(KEY_RIGHT_CONTROL);
}

bool FF_IsShiftDown() {
    return FF_IsKeyDown(KEY_LEFT_SHIFT) || FF_IsKeyDown(KEY_RIGHT_SHIFT);
}

bool FF_IsAltDown() {
    return FF_IsKeyDown(KEY_LEFT_ALT) || FF_IsKeyDown(KEY_RIGHT_ALT);
}

bool FF_IsMouseButtonDown(int button) {
    return FF_int_GetInputPtr()->mouse_pressed && FF_int_GetInputPtr()->mouse[button];
}

bool FF_IsMouseButtonPressed(int button) {
    if (FF_IsMouseButtonDown(button)) {
        FF_int_GetInputPtr()->mouse_pressed = false;
        return true;
    }
    return false;
}

//may not be very useful
bool FF_IsMouseMoving() {
    return FF_int_GetInputPtr()->mouse_offset.x != 0 || FF_int_GetInputPtr()->mouse_offset.y != 0;
}

Vec2f FF_GetMousePosition() {
    return FF_int_GetInputPtr()->mouse_pos;
}

double FF_GetMousePositionX() {
    return FF_int_GetInputPtr()->mouse_pos.x; 
}

double FF_GetMousePositionY() {
    return FF_int_GetInputPtr()->mouse_pos.y; 
}

Vec2f FF_GetMouseSpeed() {
    return FF_int_GetInputPtr()->mouse_offset;
}

double FF_GetMouseSpeedX() {
    return FF_int_GetInputPtr()->mouse_offset.x;
}

double FF_GetMouseSpeedY() {
    return FF_int_GetInputPtr()->mouse_offset.y;
}

double FF_GetMouseYaw() {
    return FF_int_GetInputPtr()->yaw;
}

double FF_GetMousePitch() {
    return FF_int_GetInputPtr()->pitch;
}

bool FF_IsScroll() {
    return FF_IsScrollUp() || FF_IsScrollDown() || FF_IsScrollRight() || FF_IsScrollLeft();
}

bool FF_IsScrollUp() {
    return FF_int_GetInputPtr()->scroll_offset.y > 0.1;
}

bool FF_IsScrollDown() {
    return FF_int_GetInputPtr()->scroll_offset.y < -0.1;
}

bool FF_IsScrollRight() {
    return FF_int_GetInputPtr()->scroll_offset.x < -0.11;
}

bool FF_IsScrollLeft() {
    return FF_int_GetInputPtr()->scroll_offset.x > 0.11;
}

Vec2f FF_GetScrollDirection() {
    float xDir = 0, yDir = 0;
    if (FF_IsScrollDown()) yDir = -1;
    if (FF_IsScrollUp()) yDir = 1;
    if (FF_IsScrollRight()) xDir = 1;
    if (FF_IsScrollLeft()) xDir = -1;
    return (Vec2f){.x=xDir, .y=yDir};
}
