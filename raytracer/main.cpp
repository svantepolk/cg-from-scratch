#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "canvas.hpp"

int main(int argc, char** argv) {
    FILE* file = fopen("output.png", "wb");
    if (!file) {
        printf("couldn't load file\n");
        return 1;
    };


    Canvas canvas;
    canvas.width = 1024;
    canvas.height = 1024;
    canvas.buffer = (uint32_t*) malloc(sizeof(uint32_t) * canvas.width * canvas.height);

    for (int y = -canvas.height / 2; y < canvas.height / 2; y++) {
        for (int x = -canvas.height / 2; x < canvas.width / 2; x++) {
            uint8_t shade = (y + x);
            set_pixel(&canvas, x, y, shade << (8 * ((x * y) % 3)));
        }
    }

    write_image(&canvas, file);
    fclose(file);

    return 0;
}
