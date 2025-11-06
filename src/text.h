#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    void draw(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color);

    TTF_Font* font() { return m_font; }

private:
    TTF_Font* m_font = nullptr;
};
