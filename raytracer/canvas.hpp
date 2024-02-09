#ifndef H_CANVAS
#define H_CANVAS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int width;
    int height;
    uint32_t* buffer;
} Canvas;

void set_pixel(Canvas* c, int x, int y, uint32_t color);
uint32_t get_pixel(Canvas* c, int x, int y);
void write_image(Canvas* c, FILE* file);

#endif
