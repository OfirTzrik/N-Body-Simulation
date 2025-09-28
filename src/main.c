#include "../include/definitions.h"

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation");
    SetTargetFPS(60);

    struct body b0 = {
        .center = {.x = WINDOW_WIDTH / 2.0, .y = WINDOW_HEIGHT / 2.0},
        .velocity = {.x = 0.0, .y = 0.0},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 64.0,
        .mass = 6.0e24,
        .color = YELLOW
    };
    struct body b1 = {
        .center = {.x = b0.center.x - 320.0, .y = b0.center.y},
        .velocity = {.x = 0.0, .y = -1.118674e3},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 20.0,
        .mass = 8.0e23,
        .color = BLUE
    };
    struct body b2 = {
        .center = {.x = b1.center.x - 40.0, .y = b1.center.y},
        .velocity = {.x = 0.0, .y = -2.274035e3},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 6.0,
        .mass = 2.0e21,
        .color = GRAY
    };

    while (!WindowShouldClose()) {
        // Simulation speed
        double dt = GetFrameTime() * 50000;

        // Zero for next time step
        b0.acceleration.x = 0;
        b0.acceleration.y = 0;
        b1.acceleration.x = 0;
        b1.acceleration.y = 0;
        b2.acceleration.x = 0;
        b2.acceleration.y = 0;

        // Calculate gravitational force between every two bodies
        calc_grav_force(&b0, &b1);
        calc_grav_force(&b0, &b2);
        calc_grav_force(&b1, &b2);
        // Update velocity with acceleration considering every two bodies
        b0.velocity.x += b0.acceleration.x * dt;
        b0.velocity.y += b0.acceleration.y * dt;
        b1.velocity.x += b1.acceleration.x * dt;
        b1.velocity.y += b1.acceleration.y * dt;
        b2.velocity.x += b2.acceleration.x * dt;
        b2.velocity.y += b2.acceleration.y * dt;

        // Update position
        // b0.center.x += (b0.velocity.x * dt) / METERS_PER_PIXEL;
        // b0.center.y += (b0.velocity.y * dt) / METERS_PER_PIXEL;
        b1.center.x += (b1.velocity.x * dt) / METERS_PER_PIXEL;
        b1.center.y += (b1.velocity.y * dt) / METERS_PER_PIXEL;
        b2.center.x += (b2.velocity.x * dt) / METERS_PER_PIXEL;
        b2.center.y += (b2.velocity.y * dt) / METERS_PER_PIXEL;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);

        draw_body(&b0);
        draw_body(&b1);
        draw_body(&b2);
        DrawLine(b1.center.x, b1.center.y, b1.center.x + b1.velocity.x / 10.0, b1.center.y + b1.velocity.y / 10.0, RED);
        DrawLine(b2.center.x, b2.center.y, b2.center.x + b2.velocity.x / 10.0, b2.center.y + b2.velocity.y / 10.0, RED);

        EndDrawing();
    }
}
