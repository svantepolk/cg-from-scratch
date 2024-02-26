#include <stdio.h>

#include "canvas.hpp"
#include "raytracer.hpp"

int main() {
    Canvas canvas;
    canvas.width = 1024;
    canvas.height = 1024;
    canvas.buffer = (uint32_t*) malloc(sizeof(uint32_t) * canvas.width * canvas.height);
    if (canvas.buffer == NULL) {
        printf("oopsie whoopsie\n");
    }

    Camera camera;
    if (canvas.width > canvas.height) {
        camera.viewport.width = 1.0f;
        camera.viewport.height = canvas.height / canvas.width;
    } else {
        camera.viewport.height = 1.0f;
        camera.viewport.width = canvas.width / canvas.height;
    }

    camera.viewport.distance = 1.0f;

    camera.position.x = 0.0f;
    camera.position.y = 0.0f;
    camera.position.z = 0.0f;
    camera.direction.x = 0.0f;
    camera.direction.y = 0.0f;
    camera.direction.z = 0.0f;

    Sphere sceneObjects[5];
    sceneObjects[0].position.x = 0.0f;
    sceneObjects[0].position.y = 1.0f;
    sceneObjects[0].position.z = 6.0f;
    sceneObjects[0].radius = 1.5f;
    sceneObjects[0].colour = 0x0000FF;

    sceneObjects[1].position.x = 2.0f;
    sceneObjects[1].position.y = 0.0f;
    sceneObjects[1].position.z = 4.0f;
    sceneObjects[1].radius = 1.0f;
    sceneObjects[1].colour = 0x00FF00;

    sceneObjects[2].position.x = -2.0f;
    sceneObjects[2].position.y = 0.0f;
    sceneObjects[2].position.z = 4.0f;
    sceneObjects[2].radius = 1.0f;
    sceneObjects[2].colour = 0xFF0000;

    sceneObjects[3].position.x = 0.0f;
    sceneObjects[3].position.y = 1.0f;
    sceneObjects[3].position.z = 3.6f;
    sceneObjects[3].radius = 0.15f;
    sceneObjects[3].colour = 0xA28B02;

    // floor
    sceneObjects[4].radius = 100.0f;
    sceneObjects[4].position.x = 0.0f;
    sceneObjects[4].position.y = 101.0f;
    sceneObjects[4].position.z = 3.0f;
    sceneObjects[4].colour = 0xFBfBFB;

    render(&canvas, &camera, sceneObjects, 5);

    FILE* file = fopen("output.png", "wb+");
    if (!file) {
        fprintf(stderr, "Unable to open file\n");
        return 1;
    };

    write_image(&canvas, file);
    fclose(file);

    return 0;
}
