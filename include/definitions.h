#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// For handling raygui warnings
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900
#define GRAV_CONSTANT 6.6743e-11
#define METERS_PER_PIXEL 1e6
#define FONT_SIZE 16
#define UI_OFFSET 8

struct vec2 {
    double x;
    double y;
};

struct body {
    int16_t identifier;
    struct vec2 center;
    struct vec2 velocity;
    struct vec2 acceleration;
    double radius;
    double mass;
    bool is_static;
    Color color;
};

void draw_body(const struct body *const b);
void calc_grav_force(struct body *const b0, struct body *const b1);
Color color_select(const int color);

#endif