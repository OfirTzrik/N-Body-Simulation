#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define GRAV_CONSTANT 6.6743e-11
#define METERS_PER_PIXEL 1e6
#define SIM_SPEED 2.5

struct vec2 {
    double x;
    double y;
};

struct body {
    struct vec2 center;
    struct vec2 velocity;
    struct vec2 acceleration;
    double radius;
    double mass;
    bool is_static;
    Color color;
};

void draw_body(struct body *b);
void calc_grav_force(struct body *b0, struct body *b1);

#endif