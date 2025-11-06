#pragma once
#include "renderer.h"
#include "text.h"
#include <string>

class Button {
public:
    Button(int x, int y, int w, int h, std::string label);

    bool update(bool mouseDown, bool mouseClicked, int mx, int my);
    void draw(Renderer& rnd) const;
    void drawText(SDL_Renderer* sdl, class TextRenderer& font) const;

private:
    int x,y,w,h;
    std::string label;
    bool hovered = false;
    bool pressed = false;
};
