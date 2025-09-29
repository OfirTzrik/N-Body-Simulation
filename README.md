# N-Body-Simulation

## Demo

![](https://github.com/OfirTzrik/N-Body-Simulation/blob/main/assets/demo.gif)

## Build
```bash
gcc src/main.c src/funcs.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -pedantic -o build/main
```

## Roadmap
- Change code accordingly for N bodies (malloc)
- Add user interface for adding new bodies (raygui)
- Switch to 3D?
- Add grid (represent space) + warp?
- Add trail and bloom
