#pragma once
#include <cstdint>

enum class Action {
    None, Up, Down, Left, Right,
    PauseToggle, Reset
};

struct InputFrame {
    bool mouseDown = false;
    int  mouseX = 0, mouseY = 0;
    bool clicked = false;
    Action action = Action::None; // one-shot, simple for now
};

// translate SDL events into one InputFrame per frame
struct Input {
    InputFrame poll();
};
