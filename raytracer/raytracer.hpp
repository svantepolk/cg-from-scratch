#ifndef H_RAYTRACER
#define H_RAYTRACER

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <limits>
#include <stdint.h>

#include "canvas.hpp"

typedef struct {
  float x;
  float y;
  float z;
} Vector3;

typedef struct {
  Vector3 position;
  float radius;
  uint32_t colour;
} Sphere;

typedef enum {
  LIGHT_POINT,
  LIGHT_DIRECTIONAL
} LightType;

typedef struct {
  Vector3 v;
  float intensity;
  LightType type;
} Light;

typedef struct {
  float width;
  float height;
  float distance;
} Viewport;

typedef struct {
  Vector3 position;
  Vector3 direction;
  Viewport viewport;
} Camera;

Vector3 Vector3Subtract(Vector3 v, Vector3 w);
Vector3 Vector3Add(Vector3 v, Vector3 w);
float Vector3Dot(Vector3 v, Vector3 w);

void render(Canvas* canvas, Camera* camera, Sphere* sceneObjects, int nSceneObjects);

#endif
