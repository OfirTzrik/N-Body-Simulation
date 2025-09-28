#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "raylib.h"

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900
#define GRAV_CONSTANT 6.6743e-11
#define METERS_PER_PIXEL 1e6

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
    Color color;
};

void draw_body(struct body *b);
void calc_grav_force(struct body *b0, struct body *b1);

#endif