# N-Body-Simulation

Using [raylib](https://www.raylib.com/) and [raygui](https://github.com/raysan5/raygui) to simulate interaction between different bodies.

## Demo

![](https://github.com/OfirTzrik/N-Body-Simulation/blob/main/assets/demo.mp4)

## Build
Uses makefile.
```bash
gcc src/main.c src/funcs.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -pedantic -o build/main
```

## Roadmap
- Change code accordingly for N bodies (malloc) - In progress
- Add user interface for adding new bodies (raygui) - In progress
- Add body preview before adding it to the simulation - In progress
- Switch to 3D?
- Add grid (represent space) + warp?
- Add trail and bloom

## Current Progress

![](https://github.com/OfirTzrik/N-Body-Simulation/blob/main/assets/current_progress.png)
