#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <png.h>

#include "canvas.hpp"

void set_pixel(Canvas* c, int x, int y, uint32_t color) {
    int rectX = c->width / 2 + x;
    int rectY = c->height / 2 + y;
    if (rectX < c->width && rectY < c->height) {
        if (rectX >= 0 && rectY >= 0) {
            c->buffer[rectY * c->width + rectX] = color;
        }
    }
}

uint32_t get_pixel(Canvas* c, int x, int y) {
    int rectX = c->width / 2 + x;
    int rectY = c->height / 2 + y;
    return c->buffer[rectY * c->width + rectX];
}

void write_image(Canvas* c, FILE* file) {
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png) {
        fclose(file);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        fclose(file);
        return;
    }

    png_init_io(png, file);

    png_set_IHDR(png, info, c->width, c->height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_text title;
    title.compression = PNG_TEXT_COMPRESSION_NONE;
    title.key = (const png_charp) "Title";
    title.text = (const png_charp) "Raytraced demo";

    png_set_text(png, info, &title, 1);
    png_write_info(png, info);

    png_byte* row = (png_byte*) malloc(3 * c->width * sizeof(png_byte));

    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            uint32_t color = c->buffer[y * c->width + x];
            png_byte* pixel = (row + x * 3);

            pixel[0] = color;
            pixel[1] = (color >> 8);
            pixel[2] = (color >> 16);
        }

        png_write_row(png, row);
    }

    png_write_end(png, NULL);
}
