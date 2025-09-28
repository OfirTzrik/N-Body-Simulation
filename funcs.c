#include "definitions.h"

void draw_body(struct body *b) {
    uint16_t resolution = 2.0 * PI * b->radius;

    for (int i = 0; i < resolution; i++) {
        double angle = 2.0 * PI * ((double)i / resolution);
        int16_t x = b->center.x + b->radius * cos(angle);
        int16_t y = b->center.y + b->radius * sin(angle);

        DrawPixel(x, y, b->color);
    }
}

void calc_grav_force(struct body *b0, struct body *b1) {
    struct vec2 dir_vector = {
        .x = b1->center.x - b0->center.x,
        .y = b1->center.y - b0->center.y
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