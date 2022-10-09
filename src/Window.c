#include "../include/Core/Window.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct _Window {
    GLFWwindow* windowPtr;
    uint16_t width;
    uint16_t height;
    int closeKey;
    bool resized, cursorLocked;
    
    float deltaTime, currentTime, lastTime;
} FF_Window;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input* i = FF_int_GetInputPtr();
    i->keys[key].prevPressed = i->keys[key].pressed;
    i->keys[key].repeat = action == GLFW_REPEAT;

    switch (action) {
        case GLFW_PRESS:
            i->keys[key].down = true;
            i->keys[key].pressed = true;
            i->keys[key].released = false;
            break;
        case GLFW_REPEAT:
            i->keys[key].down = true;
            i->keys[key].repeat = true;
            i->keys[key].released = false;
            break;
        case GLFW_RELEASE:
            i->keys[key].down = false;
            i->keys[key].pressed = false;
            i->keys[key].released = true;
            i->keys[key].repeat = false;
            break;
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Input* i = FF_int_GetInputPtr();
    i->mouse_pressed = action == GLFW_PRESS;
    if (i->mouse_pressed) {
        i->mouse[button] = true;
    }
    if (action == GLFW_RELEASE) {
        i->mouse[button] = false;
    }
}

static void mouse_cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Input* i = FF_int_GetInputPtr();
    static bool firstMouse = true;
    if (firstMouse) {
        i->last_mouse_pos.x = (float) xpos;
        i->last_mouse_pos.y = (float) ypos;
        firstMouse = false;
    }
    i->mouse_pos.x = xpos;
    i->mouse_pos.y = ypos;
    i->mouse_offset.x = xpos - i->last_mouse_pos.x;
    i->mouse_offset.y = i->last_mouse_pos.y - ypos;
    i->last_mouse_pos.x = xpos;
    i->last_mouse_pos.y = ypos;
    
    float sensitivity = 0.1f;
    i->mouse_offset.x *= sensitivity;
    i->mouse_offset.y *= sensitivity;
    
    //if (!gWindow.cursorLocked) {
        i->yaw += i->mouse_offset.x;
        i->pitch += i->mouse_offset.y;
        if (i->pitch > 89.f) 
            i->pitch = 89.f;
        if (i->pitch < -89.f)
            i->pitch = -89.f;
    //}
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
    Window* w = glfwGetWindowUserPointer(window);
    w->width = width;
    w->height = height;
    w->resized = true;
}

static void scroll_callback(GLFWwindow* window, double xoff, double yoff) {
    FF_int_GetInputPtr()->scroll_offset.x = xoff;
    FF_int_GetInputPtr()->scroll_offset.y = yoff;
}

Window* FF_CreateWindowGL(const char* name, uint16_t width, uint16_t height) {
    if (!glfwInit()) {
        LOG_WARN("Could not initialize glfw");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__ 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
   FF_Window* pWindow = malloc(sizeof(Window));
    pWindow->windowPtr = glfwCreateWindow(width, height, name, NULL, NULL);
    
    pWindow->width = width;
    pWindow->height = height;
    
    if (!pWindow->windowPtr) {
        LOG_WARN("Could not create window");
        free(pWindow);
        pWindow = NULL;
        return NULL;
    }
    
    glfwSetWindowUserPointer(pWindow->windowPtr, pWindow);
    
    glfwMakeContextCurrent(pWindow->windowPtr);
    glfwSetKeyCallback(pWindow->windowPtr, key_callback);
    glfwSetMouseButtonCallback(pWindow->windowPtr, mouse_button_callback);
    glfwSetCursorPosCallback(pWindow->windowPtr, mouse_cursor_position_callback);
    glfwSetScrollCallback(pWindow->windowPtr, scroll_callback);
    glfwSetWindowSizeCallback(pWindow->windowPtr, window_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_WARN("Failed to initialize glad");
        free(pWindow);
        pWindow = NULL;
        return NULL;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSwapInterval(1);
    
    return pWindow;
}

void FF_DestroyWindowGL(Window *pWindow) {
    glfwDestroyWindow(pWindow->windowPtr);
    pWindow->windowPtr = NULL;
    free(pWindow);
    pWindow = NULL;
}

void FF_WindowClearBackground(Window *pWindow) {
    glfwMakeContextCurrent(pWindow->windowPtr);
    FF_WindowClearBackgroundEx(pWindow, 0.4f, 0.4f, 0.4f, 1.0f);
}

void FF_WindowClearBackgroundEx(Window* pWindow, float r, float g, float b, float a) {
    glfwMakeContextCurrent(pWindow->windowPtr);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FF_SetWindowShouldClose(Window* pWindow, bool shouldClose) {
    glfwSetWindowShouldClose(pWindow->windowPtr, GLFW_TRUE);
}

void FF_WindowPollEvents(Window* pWindow) {
    glfwPollEvents();
    if (glfwGetKey(pWindow->windowPtr, pWindow->closeKey)) {
        LOG_DEBUG("Pressed the window close key");
        FF_SetWindowShouldClose(pWindow, true);
    }
}

double FF_GetTime() {
    return glfwGetTime();
}

double FF_WindowDeltaTime(Window* pWindow) {
    return pWindow->deltaTime;
}

bool FF_WindowShouldClose(Window *pWindow) {
    pWindow->currentTime = FF_GetTime();
    pWindow->deltaTime = pWindow->currentTime - pWindow->lastTime;
    pWindow->lastTime = pWindow->currentTime;
    glfwSwapBuffers(pWindow->windowPtr);
    return glfwWindowShouldClose(pWindow->windowPtr);
}

void FF_SetWindowCloseKey(Window *pWindow, int key) {
    pWindow->closeKey = key;
}

bool FF_WasWindowResized(Window *pWindow) {
    bool resized = pWindow->resized;
    pWindow->resized = false;
    return resized;
}

int FF_WindowGetWidth(Window *pWindow) {
    return pWindow->width;
}

int FF_WindowGetHeight(Window *pWindow) {
    return pWindow->height;
}

void FF_ToggleCursorLocked(Window *pWindow) {
    pWindow->cursorLocked = !pWindow->cursorLocked;
    if (pWindow->cursorLocked) {
        glfwSetInputMode(pWindow->windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(pWindow->windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

bool FF_IsCursorLocked(Window *pWindow) {
    return pWindow->cursorLocked;
}
