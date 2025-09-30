#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "../include/definitions.h"
#include "../include/raygui.h"

int main(void) {
    struct body *bodies = malloc(sizeof(struct body) * 3);
    float sim_speed = 1;
    char sim_speed_string[8] = "";
    bool id_is_active = false;
    char id_input_buffer[16] = "";
    bool posx_is_active = false;
    char posx_input_buffer[16] = "";
    bool posy_is_active = false;
    char posy_input_buffer[16] = "";
    bool velx_is_active = false;
    char velx_input_buffer[16] = "";
    bool vely_is_active = false;
    char vely_input_buffer[16] = "";
    float radius_input = 4;
    char radius_string[8] = "";
    bool mass_is_active = false;
    char mass_input_buffer[16] = "";
    bool is_static = false;
    bool color_is_open = false;
    int color_input = 0;

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

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation");
    GuiLoadStyle("assets/dark/style_dark.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Simulation speed
        double dt = GetFrameTime() * 1000 * sim_speed;

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
    
        // Add new bodies user interface
        {
            GuiPanel((Rectangle){16, 16, 256, 360}, "Add new body");

            GuiLabel((Rectangle){24, 48, 128, 16}, "Identifier:");
            if (GuiTextBox((Rectangle){100, 48, 160, 16}, id_input_buffer, 15, id_is_active)) {
                id_is_active = !id_is_active;
            }

            GuiLabel((Rectangle){24, 80, 64, 16}, "Center X:");
            if (GuiTextBox((Rectangle){92, 80, 168, 16}, posx_input_buffer, 15, posx_is_active)) {
                posx_is_active = !posx_is_active;
            }

            GuiLabel((Rectangle){24, 112, 64, 16}, "Center Y:");
            if (GuiTextBox((Rectangle){92, 112, 168, 16}, posy_input_buffer, 15, posy_is_active)) {
                posy_is_active = !posy_is_active;
            }

            GuiLabel((Rectangle){24, 144, 128, 16}, "Velocity X:");
            if (GuiTextBox((Rectangle){100, 144, 160, 16}, velx_input_buffer, 15, velx_is_active)) {
                velx_is_active = !velx_is_active;
            }

            GuiLabel((Rectangle){24, 176, 128, 16}, "Velocity Y:");
            if (GuiTextBox((Rectangle){100, 176, 160, 16}, vely_input_buffer, 15, vely_is_active)) {
                vely_is_active = !vely_is_active;
            }

            GuiLabel((Rectangle){24, 208, 64, 16}, "Radius:");
            GuiSlider((Rectangle){80, 208, 180, 16}, "", "", &radius_input, 4, 64);
            sprintf(radius_string, "%.0f", radius_input);
            GuiLabel((Rectangle){160, 208, 180, 16}, radius_string);

            GuiLabel((Rectangle){24, 240, 64, 16}, "Mass:");
            if (GuiTextBox((Rectangle){70, 240, 190, 16}, mass_input_buffer, 15, mass_is_active)) {
                mass_is_active = !mass_is_active;
            }
            GuiLabel((Rectangle){24, 272, 64, 16}, "Is Static:");
            GuiCheckBox((Rectangle){100, 272, 160, 16}, "", &is_static);

            GuiLabel((Rectangle){24, 304, 64, 16}, "Color:");
            if (GuiDropdownBox((Rectangle){72, 304, 188, 16}, "Red;Green;Blue;Yellow", &color_input, color_is_open)) {
                color_is_open = !color_is_open;
            }
            if (!color_is_open) {
                GuiButton((Rectangle){24, 336, 240, 32}, "Add Body");
            }
        }
        
        {
            GuiPanel((Rectangle){16, 392, 256, 312}, "Bodies added");
        }

        {
            GuiPanel((Rectangle){288, 648, WINDOW_WIDTH - 304, 56}, "Simluation speed");

            GuiSlider((Rectangle){296, 680, WINDOW_WIDTH - 320, 16}, "", "", &sim_speed, 1, 50);
            sprintf(sim_speed_string, "%.0f", sim_speed);
            GuiLabel((Rectangle){780, 680, WINDOW_WIDTH - 304, 16}, sim_speed_string);
        }

        EndDrawing();
    }

    free(bodies);
}
