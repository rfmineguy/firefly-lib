#include <stdio.h>
#include "../libs/stb/stb_image.h"

int main() {
    printf("Hello World from test_main.c\n");
    stbi_set_flip_vertically_on_load(1);
}
