#include "../include/definitions.h"

/*
Draw a circle from scratch (instead of using raylib's builtin DrawCircle method)

@param b    Circle to draw
*/
void draw_body(const struct body *const b) {
    if (b == NULL) {
        return;
    }

    uint16_t resolution = 2.0 * PI * (b->radius);

    for (int i = 0; i < resolution; i++) {
        double angle = 2.0 * PI * ((double)i / resolution);
        int16_t x = b->center.x + (b->radius) * cos(angle);
        int16_t y = b->center.y + (b->radius) * sin(angle);

        DrawPixel(x, y, b->color);
    }
}

/*
Calculate the gravitational force between 2 bodies

@param *b0  First body
@param *b1  Second body
*/
void calc_grav_force(struct body *const b0, struct body *const b1) {
    if (b0 == NULL || b1 == NULL) {
        return;
    }

    struct vec2 dir_vec = {
        .x = (b1->center.x - b0->center.x) * METERS_PER_PIXEL,
        .y = (b1->center.y - b0->center.y) * METERS_PER_PIXEL
    };

    // 0.001 to avoid division by zero in force_general
    double dist = sqrt(dir_vec.x * dir_vec.x + dir_vec.y * dir_vec.y + 0.001);

    struct vec2 norm_vec = {
        .x = dir_vec.x / dist,
        .y = dir_vec.y / dist
    };

    double force_general = GRAV_CONSTANT * (b0->mass * b1->mass / (dist * dist));
    struct vec2 force = {
        .x = force_general * norm_vec.x,
        .y = force_general * norm_vec.y,
    };

    b0->acceleration.x += force.x / b0->mass;
    b0->acceleration.y += force.y / b0->mass;
    b1->acceleration.x += -force.x / b1->mass;
    b1->acceleration.y += -force.y / b1->mass;
}

/*
Select the appropriate color based on the numberpassed from raygui's dropdown menu

@param color    Number representing the color selected
*/
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