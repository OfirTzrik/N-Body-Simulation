#include "../include/definitions.h"

void draw_body(struct body *b) {
    uint16_t resolution = 2.0 * PI * (b->radius);

    for (int i = 0; i < resolution; i++) {
        double angle = 2.0 * PI * ((double)i / resolution);
        int16_t x = b->center.x + (b->radius) * cos(angle);
        int16_t y = b->center.y + (b->radius) * sin(angle);

        DrawPixel(x, y, b->color);
    }
}

void calc_grav_force(struct body *b0, struct body *b1) {
    struct vec2 dir_vector = {
        .x = (b1->center.x - b0->center.x) * METERS_PER_PIXEL,
        .y = (b1->center.y - b0->center.y) * METERS_PER_PIXEL
    };
    double distance = sqrt(dir_vector.x * dir_vector.x + dir_vector.y * dir_vector.y + 0.01);
    struct vec2 unit_vector = {
        .x = dir_vector.x / distance,
        .y = dir_vector.y / distance
    };
    struct vec2 force = {
        .x = GRAV_CONSTANT * (b0->mass * b1->mass / (distance * distance)) * unit_vector.x,
        .y = GRAV_CONSTANT * (b0->mass * b1->mass / (distance * distance)) * unit_vector.y,
    };

    b0->acceleration.x += force.x / b0->mass;
    b0->acceleration.y += force.y / b0->mass;
    b1->acceleration.x += -force.x / b1->mass;
    b1->acceleration.y += -force.y / b1->mass;
}

Color color_select(const int color) {
    switch (color) {
        case 0:
            return GRAY;
        case 1:
            return GOLD;
        case 2:
            return ORANGE;
        case 3:
            return PINK;
        case 4:
            return MAROON;
        case 5:
            return LIME;
        case 6:
            return SKYBLUE;
        case 7:
            return VIOLET;
        case 8:
            return BEIGE;
        case 9:
            return BROWN;
        default:
            return RAYWHITE;
    }
}