#include "../include/Core/Input.h"
#include <stdio.h>

typedef struct _KeyBind {

} KeyBind;

static Input gInput;

Input* GetInputPtr() {
    return &gInput;
}

bool IsKeyDown(int key) {
    return GetInputPtr()->keys[key];
}
