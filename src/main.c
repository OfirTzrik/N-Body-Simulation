#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "../include/definitions.h"
#include "../include/raygui.h"

int main(void) {
    // Variables
    struct body *bodies = malloc(sizeof(struct body) * 3);

    float sim_speed = 75;
    float posx_input = 714;
    float posy_input = 605;
    float radius_input = 12;
    
    bool id_is_active = false;
    bool velx_is_active = false;
    bool vely_is_active = false;
    bool mass_is_active = false;
    bool is_static = false;
    bool color_is_open = false;
    bool remove_is_active = false;

    char id_input_buffer[4] = "";
    char velx_input_buffer[16] = "";
    char vely_input_buffer[16] = "";
    char mass_input_buffer[16] = "";
    char remove_input_buffer[4] = "";
    
    int color_input = 0;

    bodies[0] = (struct body){
        .identifier = 286,
        .center = {.x = WINDOW_WIDTH / 2.0 + 128, .y = WINDOW_HEIGHT / 2.0},
        .velocity = {.x = 0.0, .y = 0.0},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 64.0,
        .mass = 6.0e24,
        .is_static = true,
        .color = YELLOW,
        .next = NULL
    };
    bodies[1] = (struct body){
        .identifier = 837,
        .center = {.x = bodies[0].center.x - 320.0, .y = bodies[0].center.y},
        .velocity = {.x = 0.0, .y = -1.118674e3},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 20.0,
        .mass = 8.0e23,
        .is_static = false,
        .color = BLUE,
        .next = NULL
    };
    bodies[2] = (struct body){
        .identifier = 194,
        .center = {.x = bodies[1].center.x - 40.0, .y = bodies[1].center.y},
        .velocity = {.x = 0.0, .y = -2.274035e3},
        .acceleration = {.x = 0.0, .y = 0.0},
        .radius = 6.0,
        .mass = 2.0e21,
        .is_static = false,
        .color = GRAY,
        .next = NULL
    };

    // Window initialization
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation");
    GuiLoadStyle("assets/dark/style_dark.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Simulation speed
        double dt = GetFrameTime() * 100 * sim_speed;

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
            if (GuiTextBox((Rectangle){100, 48, 160, 16}, id_input_buffer, 4, id_is_active)) {
                id_is_active = !id_is_active;
            }

            GuiLabel((Rectangle){24, 80, 64, 16}, "Center X:");
            GuiSlider((Rectangle){92, 80, 168, 16}, "", "", &posx_input, 512, 1024);

            GuiLabel((Rectangle){24, 112, 64, 16}, "Center Y:");
            GuiSlider((Rectangle){92, 112, 168, 16}, "", "", &posy_input, 512, 1024);

            GuiLabel((Rectangle){24, 144, 128, 16}, "Velocity X:");
            if (GuiTextBox((Rectangle){100, 144, 160, 16}, velx_input_buffer, 16, velx_is_active)) {
                velx_is_active = !velx_is_active;
            }

            GuiLabel((Rectangle){24, 176, 128, 16}, "Velocity Y:");
            if (GuiTextBox((Rectangle){100, 176, 160, 16}, vely_input_buffer, 16, vely_is_active)) {
                vely_is_active = !vely_is_active;
            }

            GuiLabel((Rectangle){24, 208, 64, 16}, "Radius:");
            GuiSlider((Rectangle){80, 208, 180, 16}, "", "", &radius_input, 4, 64);

            GuiLabel((Rectangle){24, 240, 64, 16}, "Mass:");
            if (GuiTextBox((Rectangle){70, 240, 190, 16}, mass_input_buffer, 16, mass_is_active)) {
                mass_is_active = !mass_is_active;
            }
            GuiLabel((Rectangle){24, 272, 64, 16}, "Is Static:");
            GuiCheckBox((Rectangle){92, 272, 168, 16}, "", &is_static);

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

            GuiLabel((Rectangle){24, 424, 64, 16}, "Remove:");
            if (GuiTextBox((Rectangle){84, 424, 128, 16}, remove_input_buffer, 4, remove_is_active)) {
                remove_is_active = !remove_is_active;
            }
            GuiButton((Rectangle){224, 424, 40, 16}, "X");
        }

        {
            GuiPanel((Rectangle){288, 648, WINDOW_WIDTH - 304, 56}, "Simluation speed");

            GuiSlider((Rectangle){296, 680, WINDOW_WIDTH - 320, 16}, "", "", &sim_speed, 1, 500);
        }

        EndDrawing();
    }

    free(bodies);
}
