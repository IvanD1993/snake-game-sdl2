#pragma once
#include <SDL.h>

class Renderer {
public:
    Renderer(int width, int height, const char* title);
    ~Renderer();

    // non-copy
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(int r, int g, int b, int a = 255);
    void fillRect(int x, int y, int w, int h, int r, int g, int b, int a = 255);
    void drawRect(int x, int y, int w, int h, int r, int g, int b, int a = 255);
    void present();

    SDL_Renderer* raw() { return m_renderer; }
    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    SDL_Window*   m_window   = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    int m_width = 0, m_height = 0;
};
