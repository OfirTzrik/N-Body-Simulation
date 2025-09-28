#include "definitions.h"

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation");
    SetTargetFPS(60);

    // Earth-like
    struct body b0 = {
        .center = {.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2},
        .velocity = {.x = 0, .y = 0},
        .acceleration = {.x = 0, .y = 0},
        .radius = 63,
        .mass = 8.948e16,
        .color = BLUE
    };
    // Moon-like
    struct body b1 = {
        .center = {.x = b0.center.x - 200, .y = b0.center.y},
        .velocity = {.x = 0, .y = -170.15},
        .acceleration = {.x = 0, .y = 0},
        .radius = 17,
        .mass = 1.213e11,
        .color = RAYWHITE
    };

    while (!WindowShouldClose()) {
        // Simulation speed
        double dt = GetFrameTime();

        // Zero for next time step
        b0.acceleration.x = 0;
        b0.acceleration.y = 0;
        b1.acceleration.x = 0;
        b1.acceleration.y = 0;

        // Calculate gravitational force between every two bodies
        calc_grav_force(&b0, &b1);
        // Update velocity with acceleration considering every two bodies
        b0.velocity.x += b0.acceleration.x * dt;
        b0.velocity.y += b0.acceleration.y * dt;
        b1.velocity.x += b1.acceleration.x * dt;
        b1.velocity.y += b1.acceleration.y * dt;

        // Update position
        b0.center.x += b0.velocity.x * dt;
        b0.center.y += b0.velocity.y * dt;
        b1.center.x += b1.velocity.x * dt;
        b1.center.y += b1.velocity.y * dt;

        BeginDrawing();
        ClearBackground(BLACK);

        draw_body(&b0);
        draw_body(&b1);
        DrawLine(b1.center.x, b1.center.y, b1.center.x + b1.velocity.x, b1.center.y + b1.velocity.y, RED);

        EndDrawing();
    }
}
