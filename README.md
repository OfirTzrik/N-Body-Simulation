# N-Body-Simulation

Minimal N-body gravity simulator built with [raylib](https://www.raylib.com/) and [raygui](https://github.com/raysan5/raygui).

## Demo

![](https://github.com/OfirTzrik/N-Body-Simulation/blob/main/assets/demo.gif)

## Features
- Real-time Newtonian gravity
- Multiple bodies with configurable mass and velocity
- Simple UI via raygui for adding and removing bodies (WIP)

## Build
This repo uses a makefile.
### Linux (Debian/Ubuntu)
```bash
sudo apt-get update
sudo apt-get install -y build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```
Follow "[Building raylib with CMake](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#build-raylib-using-cmake)" and then:
```bash
git clone https://github.com/OfirTzrik/Spline.git
cd Spline
make

./build/main
```

## Roadmap
- Dynamic allocation for true N bodies - WIP
- User interface for removing bodies - WIP
- Optional 3D mode
- Grid (represent space) + warp
- Trail and bloom
