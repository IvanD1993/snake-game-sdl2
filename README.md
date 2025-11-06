# 🐍 snake game (C++ / SDL2 / WSL)

A minimal 2D snake game skeleton and prototype built with **CMake**, **SDL2**, and **SDL_ttf**.  
Runs natively in **WSL (Ubuntu)** or Linux, with full **VS Code integration**.

---

## 📦 Prerequisites (Ubuntu / WSL)

Install the required build tools and libraries:

```bash
sudo apt update
sudo apt install -y cmake ninja-build g++ libsdl2-dev libsdl2-ttf-dev

🏗️ Build & Run (VS Code + CMake Tools)

In VS Code, open the Command Palette →
CMake: Select Configure Preset → choose linux-debug

Build using Ctrl + Shift + B
or run manually:

cmake --preset linux-debug
cmake --build --preset debug

🧰 Features

Fixed-timestep update loop (120 Hz logic)
Menu / Playing / Paused states
Buttons with SDL_ttf text labels
Modular, small, and easy to extend
Ready-to-run on WSL or Linux
CMake + Ninja + VS Code integration