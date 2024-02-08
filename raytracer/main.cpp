#include <stdio.h>
#include <stdlib.h>
#include <png.h>

FILE* load_file(char* path) {
    FILE* file = fopen(path, "wb");
    return file;
}


void setRGB(png_byte* pixel, int width, int height, int x, int y) {
    png_byte r = 255;
    png_byte g = 255;
    png_byte b = 255;

    pixel[0] = r * (y * width + x) / (width * height);
    pixel[1] = g * (y * width + x) / (width * height);
    pixel[2] = b * (y * width + x) / (width * height);
}

int write_image(FILE* file) {

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png) {
        printf("can't init png\n");
        fclose(file);
        return 0;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        printf("can't init info\n");
        fclose(file);
        return 0;
    }

    png_init_io(png, file);

    int width = 1024;
    int height = 1024;

    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_text title;
    title.compression = PNG_TEXT_COMPRESSION_NONE;
    title.key = "Title";
    title.text = "Raytraced demo";

    png_set_text(png, info, &title, 1);
    png_write_info(png, info);

    png_byte* row = (png_byte*) malloc(3 * width * sizeof(png_byte));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            setRGB(row + (x * 3), width, height, x, y);
        }

        png_write_row(png, row);
    }

    png_write_end(png, NULL);

    return 1;
}

int main(int argc, char** argv) {
    FILE* f = load_file("output.png");
    if (!f) {
        printf("couldn't load file\n");
        return 1;
    };

    if (!write_image(f)) {
      printf("didn't work\n");
    }

    fclose(f);

    return 0;
}
