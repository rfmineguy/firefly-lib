#include "../include/Core/Window.h"
#include "../include/Core/Input.h"
#include "../include/IO/Log.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct _Window {
    GLFWwindow* windowPtr;
    int width;
    int height;
    int closeKey;
} Window;

static Window gWindow;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input* i = GetInputPtr();
    i->key_repeat = action == GLFW_REPEAT;
    i->key_pressed = action == GLFW_PRESS;
    if (i->key_pressed) {
        i->keys[key] = true;
    }
    if (action == GLFW_RELEASE) {
        i->keys[key] = false;
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Input* i = GetInputPtr();
    i->mouse_pressed = action == GLFW_PRESS;
    if (i->mouse_pressed) {
        i->mouse[button] = true;
    }
    if (action == GLFW_RELEASE) {
        i->mouse[button] = false;
    }
}

static void mouse_cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Input* i = GetInputPtr();
    i->last_mouse_pos = i->mouse_pos;

    i->mouse_pos.x = (float) xpos;
    i->mouse_pos.y = (float) ypos;

    i->mouse_velocity = (Vec2f) {.x = i->mouse_pos.x - i->last_mouse_pos.x, .y = i->mouse_pos.y - i->last_mouse_pos.y };
    printf("%0.4f, %0.4f\n", xpos, ypos);
    printf("%0.4f, %0.4f\n", i->mouse_velocity.x, i->mouse_velocity.y);
}

void InitWindowAPI(API api) {
    gWindow.closeKey = GLFW_KEY_ESCAPE;
    if (api == OPENGL) InitWindowGL();
    if (api == VULKAN) InitWindowVK();
    if (api == METAL) InitWindowMTL();
}

void InitWindowAPIEx(API api, const char* title, int width, int height) {
    if (api == OPENGL) InitWindowGLEx(title, width, height);
    if (api == VULKAN) InitWindowVKEx(title, width, height);
    if (api == METAL) InitWindowMTLEx(title, width, height);
}

void InitWindowGL() {
    InitWindowGLEx("Default Window (OpenGL)", 600, 600);
}

void InitWindowGLEx(const char* title, int width, int height) {
    fprintf(stderr, "Initializing GL is not implemented\n");
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize glfw\n");
        exit(1);
    }
    gWindow.windowPtr = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!gWindow.windowPtr) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(gWindow.windowPtr);
    glfwSetKeyCallback(gWindow.windowPtr, key_callback);
    glfwSetMouseButtonCallback(gWindow.windowPtr, mouse_button_callback);
    glfwSetCursorPosCallback(gWindow.windowPtr, mouse_cursor_position_callback);
}

void InitWindowVK() {
    InitWindowVKEx("Default Window (Vulkan)", 600, 600);
}

void InitWindowVKEx(const char* title, int width, int height) {
    fprintf(stderr, "Initializing Vulkan is not implemented\n");
}

void InitWindowMTL() {
    InitWindowMTLEx("Default Window (Metal)", 600, 600);
}

void InitWindowMTLEx(const char* title, int width, int height) {
    fprintf(stderr, "Initializing Metal is not implemented\n");
}

void DestroyWindowGL() {
    glfwDestroyWindow(gWindow.windowPtr);
    glfwTerminate();
}

void SetWindowShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(gWindow.windowPtr, GLFW_TRUE);
}

void WindowPollEvents() {
    glfwPollEvents();
    if (glfwGetKey(gWindow.windowPtr, gWindow.closeKey)) {
        LOG_DEBUG("Pressed the window close key");
        SetWindowShouldClose(true);
    }
}

bool WindowShouldClose() {
    return glfwWindowShouldClose(gWindow.windowPtr);
}

void SetWindowCloseKey(int key) {
    gWindow.closeKey = key;
}
