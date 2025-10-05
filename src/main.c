#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "../include/definitions.h"
#include "../include/raygui.h"

int main(void) {
    // Variables
    struct body *bodies = malloc(sizeof(struct body) * 4); // Initial size of 4

    float sim_speed = 0;
    float posx_input = 750;
    float posy_input = 340;
    float radius_input = 12;
    
    bool id_is_active = false;
    bool velx_is_active = false;
    bool vely_is_active = false;
    bool mass_is_active = false;
    bool is_static = false;
    bool color_is_open = false;
    bool remove_is_active = false;

    char id_input_buffer[4] = "0";
    char velx_input_buffer[16] = "0";
    char vely_input_buffer[16] = "0";
    char mass_input_buffer[16] = "1";
    char remove_input_buffer[4] = "";
    
    size_t arr_cap = 4;
    size_t arr_size = 0;
    int color_input = 0;

    // Window initialization
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation");
    GuiLoadStyle("assets/dark/style_dark.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Simulation speed
        double dt = GetFrameTime() * sim_speed;

        // Zero for next time step
        for (size_t i = 0; i < arr_size; i++) {
            (*(bodies + i)).acceleration.x = 0;
            (*(bodies + i)).acceleration.y = 0;
        }

        // Calculate gravitational force between every two bodies
        for (size_t i = 0; i < arr_size; i++) {
            for(size_t j = i; j < arr_size; j++) {
                if (i == j) {
                    continue;
                }
                calc_grav_force((bodies + i), (bodies + j));
            }
        }

        // Update velocity with acceleration considering every two bodies
        for (size_t i = 0; i < arr_size; i++) {
            if (!(*(bodies + i)).is_static) {
                (*(bodies + i)).velocity.x += (*(bodies + i)).acceleration.x * dt;
                (*(bodies + i)).velocity.y += (*(bodies + i)).acceleration.y * dt;
                (*(bodies + i)).center.x += ((*(bodies + i)).velocity.x * dt) / METERS_PER_PIXEL;
                (*(bodies + i)).center.y += ((*(bodies + i)).velocity.y * dt) / METERS_PER_PIXEL;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(WINDOW_WIDTH - 82, 10);
        
        // Draw bodies
        for (size_t i = 0; i < arr_size; i++) {
            draw_body(bodies + i);
        }

        // Draw velocity vector
        for(size_t i = 0; i < arr_size; i++) {
            if (!(*(bodies + i)).is_static) {
                DrawLine(
                    (*(bodies + i)).center.x,
                    (*(bodies + i)).center.y,
                    (*(bodies + i)).center.x + (*(bodies + i)).velocity.x / 10,
                    (*(bodies + i)).center.y + (*(bodies + i)).velocity.y / 10,
                    RED
                );
            }
        }
    
        // User interface
        {
            // Add new bodies user interface
            {
                GuiPanel((Rectangle){UI_OFFSET, UI_OFFSET, 200, 288}, "Add new body");

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 32, 128, 16}, "Identifier:");
                if (GuiTextBox((Rectangle){104, UI_OFFSET + 32, 96, 16}, id_input_buffer, 4, id_is_active)) {
                    id_is_active = !id_is_active;
                }

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 56, 128, 16}, "Center X:");
                GuiSlider((Rectangle){104, UI_OFFSET + 56, 96, 16}, "", "", &posx_input, 268, 1400);

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 80, 128, 16}, "Center Y:");
                GuiSlider((Rectangle){104, UI_OFFSET + 80, 96, 16}, "", "", &posy_input, 40, 800);

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 104, 128, 16}, "Velocity X:");
                if (GuiTextBox((Rectangle){104, UI_OFFSET + 104, 96, 16}, velx_input_buffer, 16, velx_is_active)) {
                    velx_is_active = !velx_is_active;
                }

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 128, 128, 16}, "Velocity Y:");
                if (GuiTextBox((Rectangle){104, UI_OFFSET + 128, 96, 16}, vely_input_buffer, 16, vely_is_active)) {
                    vely_is_active = !vely_is_active;
                }

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 152, 64, 16}, "Radius:");
                GuiSlider((Rectangle){104, UI_OFFSET + 152, 96, 16}, "", "", &radius_input, 4, 64);

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 176, 64, 16}, "Mass:");
                if (GuiTextBox((Rectangle){104, UI_OFFSET + 176, 96, 16}, mass_input_buffer, 16, mass_is_active)) {
                    mass_is_active = !mass_is_active;
                }
                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 200, 64, 16}, "Is Static:");
                GuiCheckBox((Rectangle){104, UI_OFFSET + 200, 96, 16}, "", &is_static);

                GuiLabel((Rectangle){UI_OFFSET + 8, UI_OFFSET + 224, 64, 16}, "Color:");
                if (GuiDropdownBox((Rectangle){104, UI_OFFSET + 224, 96, 16}, "Gray;Gold;Orange;Pink;Maroon;Lime;Sky blue;Violet;Beige;Brown", &color_input, color_is_open)) {
                    color_is_open = !color_is_open;
                }
                if (!color_is_open) {
                    if(GuiButton((Rectangle){UI_OFFSET + 8, UI_OFFSET + 248, 184, 32}, "Add Body") && arr_size < arr_cap) {
                        bodies[arr_size++] = (struct body) {
                            .identifier = 15,
                            .center = {posx_input, posy_input},
                            .velocity = {atof(velx_input_buffer), atof(vely_input_buffer)},
                            .acceleration = {0, 0},
                            .radius = radius_input,
                            .mass = atof(mass_input_buffer),
                            .is_static = is_static,
                            .color = color_select(color_input),
                            .next = NULL
                        };
                    }
                }
            }

            // List of added body and removal
            {
                GuiPanel((Rectangle){UI_OFFSET, WINDOW_HEIGHT - 312 - UI_OFFSET, 200, 312}, "Bodies added");

                GuiLabel((Rectangle){UI_OFFSET + 8, WINDOW_HEIGHT - 280 - UI_OFFSET, 128, 16}, "Remove:");
                if (GuiTextBox((Rectangle){80, WINDOW_HEIGHT - 280 - UI_OFFSET, 64, 16}, remove_input_buffer, 4, remove_is_active)) {
                    remove_is_active = !remove_is_active;
                }
                GuiButton((Rectangle){160, WINDOW_HEIGHT - 280 - UI_OFFSET, 40, 16}, "X");
            }

            // Control simulation speed
            {
                GuiPanel((Rectangle){UI_OFFSET + 208, WINDOW_HEIGHT - 56 - UI_OFFSET, WINDOW_WIDTH - 216 - UI_OFFSET, 56}, "Simluation speed");

                GuiSlider((Rectangle){UI_OFFSET + 216, WINDOW_HEIGHT - 24 - UI_OFFSET, WINDOW_WIDTH - 232 - UI_OFFSET, 16}, "", "", &sim_speed, 0, 10000);
            }
        }

        // Draw preview of the body that is going to be added
        struct body preview_body = {
            .identifier = 999,
            .center = {posx_input, posy_input},
            .velocity = {atof(velx_input_buffer), atof(vely_input_buffer)},
            .acceleration = {0, 0},
            .radius = radius_input,
            .mass = atof(mass_input_buffer),
            .is_static = false,
            .color = color_select(color_input),
            .next = NULL
        };
        draw_body(&preview_body);

        EndDrawing();
    }

    // Exit program
    free(bodies);
    return EXIT_SUCCESS;
}
