#include "../include/Core/Window.h"
#include "../include/IO/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct _Window {
    GLFWwindow* window;
    int width;
    int height;
} Window;

void InitWindowAPI(API api) {
    if (api == OPENGL) InitWindowGL();
    if (api == VULKAN) InitWindowVK();
    if (api == METAL) InitWindowMTL();
}

void InitWindowGL() {
    InitWindowGLEx("Default Window (OpenGL)", 600, 600);
}

void InitWindowGLEx(const char* title, int width, int height) {
    fprintf(stderr, "Initializing GL is not implemented\n");
}

void InitWindowVK() {
    InitWindowVKEx("Default Window (Vulkan)", 600, 600);
}

void InitWindowVKEx(const char* title, int width, int height) {
    fprintf(stderr, "Initializing Vulkan is not implemented\n");
}
