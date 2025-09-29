#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "../include/definitions.h"
#include "../include/raygui.h"

int main(void) {
    struct body *bodies = malloc(sizeof(struct body) * 3);
    char id_input_buffer[16] = "";
    float posx_input;
    float posy_input;
    float velocityx_input;
    float velocityy_input;

    bodies[0] = (struct body){
        .center = {.x = WINDOW_WIDTH / 2.0 + 128, .y = WINDOW_HEIGHT / 2.0},
        .velocity = {.x = 0.0, .y = 0.0},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 64.0,
        .mass = 6.0e24,
        .is_static = true,
        .color = YELLOW
    };
    bodies[1] = (struct body){
        .center = {.x = bodies[0].center.x - 320.0, .y = bodies[0].center.y},
        .velocity = {.x = 0.0, .y = -1.118674e3},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 20.0,
        .mass = 8.0e23,
        .is_static = false,
        .color = BLUE
    };
    bodies[2] = (struct body){
        .center = {.x = bodies[1].center.x - 40.0, .y = bodies[1].center.y},
        .velocity = {.x = 0.0, .y = -2.274035e3},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 6.0,
        .mass = 2.0e21,
        .is_static = false,
        .color = GRAY
    };

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation");
    GuiLoadStyle("assets/dark/style_dark.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Simulation speed
        double dt = GetFrameTime() * 5000 * SIM_SPEED;

        // Zero for next time step
        for (size_t i = 0; i < 3; i++) {
            (*(bodies + i)).acceleration.x = 0;
            (*(bodies + i)).acceleration.y = 0;
        }

        // Calculate gravitational force between every two bodies
        for (size_t i = 0; i < 3; i++) {
            for(size_t j = i; j < 3; j++) {
                if (i == j) {
                    continue;
                }
                calc_grav_force((bodies + i), (bodies + j));
            }
        }
        // Update velocity with acceleration considering every two bodies
        for (size_t i = 0; i < 3; i++) {
            (*(bodies + i)).velocity.x += (*(bodies + i)).acceleration.x * dt;
            (*(bodies + i)).velocity.y += (*(bodies + i)).acceleration.y * dt;
        }

        // Update position
        for (size_t i = 1; i < 3; i++) {
            (*(bodies + i)).center.x += ((*(bodies + i)).velocity.x * dt) / METERS_PER_PIXEL;
            (*(bodies + i)).center.y += ((*(bodies + i)).velocity.y * dt) / METERS_PER_PIXEL;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(WINDOW_WIDTH - 82, 10);

        // Control panel user interface
        GuiPanel((Rectangle){16, 16, 256, WINDOW_HEIGHT - 32}, "Control Panel");

        GuiLabel((Rectangle){24, 48, 128, 16}, "Identifier:");
        GuiTextBox((Rectangle){100, 48, 160, 16}, id_input_buffer, 15, true);

        GuiLabel((Rectangle){24, 80, 64, 16}, "Center X:");
        GuiSlider((Rectangle){92, 80, 168, 16}, "", "", &posx_input, 0, 500);

        GuiLabel((Rectangle){24, 112, 64, 16}, "Center Y:");
        GuiSlider((Rectangle){92, 112, 168, 16}, "", "", &posy_input, 0, 500);

        GuiLabel((Rectangle){24, 144, 128, 16}, "Velocity X:");
        GuiSlider((Rectangle){100, 144, 160, 16}, "", "", &velocityx_input, 0, 500);

        GuiLabel((Rectangle){24, 176, 128, 16}, "Velocity Y:");
        GuiSlider((Rectangle){100, 176, 160, 16}, "", "", &velocityy_input, 0, 500);

        GuiLabel((Rectangle){24, 208, 128, 16}, "Acceleration X:");
        GuiLabel((Rectangle){24, 240, 128, 16}, "Acceleration Y:");
        GuiLabel((Rectangle){24, 272, 64, 16}, "Radius:");
        GuiLabel((Rectangle){24, 304, 64, 16}, "Mass:");
        GuiLabel((Rectangle){24, 336, 64, 16}, "Is Static:");
        GuiLabel((Rectangle){24, 368, 64, 16}, "Color:");
        GuiButton((Rectangle){24, 400, 240, 32}, "Add Body");
        
        // Draw bodies
        for (size_t i = 0; i < 3; i++) {
            draw_body(bodies + i);
        }

        // Draw velocity vector
        for(size_t i = 0; i < 3; i++) {
            if (!(*(bodies + i)).is_static) {
                DrawLine((*(bodies + i)).center.x, (*(bodies + i)).center.y, (*(bodies + i)).center.x + (*(bodies + i)).velocity.x / 10, (*(bodies + i)).center.y + (*(bodies + i)).velocity.y / 10, RED);
            }
        }

        EndDrawing();
    }

    free(bodies);
}
