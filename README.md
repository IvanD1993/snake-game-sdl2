# snake_engine (WSL + SDL2 minimal)

Minimal CMake + SDL2 starter that opens a window, runs a fixed-timestep loop, and clears the screen.

## Prereqs (Ubuntu 24.04 in WSL)

```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build pkg-config libsdl2-dev
```

## Build (VS Code with CMake Tools)

- Open this folder in VS Code **from WSL** (`code .`).
- In the **Command Palette**, run: `CMake: Select Configure Preset` → `Linux Debug (Ninja)`
- Then run `CMake: Build`.

Or build manually:

```bash
cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug
./build/debug/snake
```

You should see a 1280×720 window with the title "snake (SDL2)" and an FPS counter in the console.

## Files

- `CMakeLists.txt` – project config
- `src/main.cpp` – entry point
- `src/app.cpp` – SDL setup + fixed-step loop
