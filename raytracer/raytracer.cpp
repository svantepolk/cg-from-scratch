#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <limits>
#include <cmath>

#include "raytracer.hpp"

Vector3 Vector3Subtract(Vector3 v, Vector3 w) {
    Vector3 result;
    result.x = v.x - w.x;
    result.y = v.y - w.y;
    result.z = v.z - w.z;
    return result;
}

float Vector3Dot(Vector3 v, Vector3 w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

/*
 * This will set both floats to the same value if there's only one hit.
 */
int RaySphereIntersection(Vector3 origin, Vector3 direction, Sphere sphere, float* t1, float* t2) {
    // get the magnitude squared
    Vector3 oc = Vector3Subtract(origin, sphere.position);

    float a = Vector3Dot(direction, direction);
    float b = 2 * Vector3Dot(oc, direction);
    float c = Vector3Dot(oc, oc) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    }

    *t1 = (-b + sqrt(discriminant)) / (2 * a);
    *t2 = (-b - sqrt(discriminant)) / (2 * a);

    if (discriminant == 0) {
        return 1;
    }
    return 2;
}

uint32_t TraceRay(Vector3 origin, Vector3 direction, float min_distance, Sphere* sceneObjects, int nSceneObjects) {
    int closestIndex = -1;
    float closest = std::numeric_limits<float>::max();

    for (int i = 0; i < nSceneObjects; i++) {
        float t1, t2;

        if (RaySphereIntersection(origin, direction, sceneObjects[i], &t1, &t2)) {
          if (t1 > min_distance) {
              if (t1 < closest) {
                closest = t1;
                closestIndex = i;
              }
          }
          if (t2 > min_distance) {
              if (t2 < closest) {
                closest = t2;
                closestIndex = i;
              }
          }
        }
    }
    if (closestIndex > -1) {
        return sceneObjects[closestIndex].colour;
    } else {
        return 0x000000;
    }
}


void render(Canvas* canvas, Camera* camera, Sphere* sceneObjects, int nSceneObjects) {
    for (int y = -canvas->height/2; y < canvas->height/2; y++) {
        for (int x = -canvas->width/2; x < canvas->width/2; x++) {
          Vector3 direction;
          direction.x = x * camera->viewport.width / canvas->width;
          direction.y = y * camera->viewport.height / canvas->height;
          // TODO: this line breaks when rotating the camera. need to consider direction
          direction.z = 1; //camera->position.z + camera->viewport.distance;
          uint32_t colour = TraceRay(camera->position, direction, 1.0f, sceneObjects, nSceneObjects);
          set_pixel(canvas, x, y, colour);
        }
    }
}
