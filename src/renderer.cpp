#include "renderer.h"
#include <iostream>

Renderer::Renderer(int width, int height, const char* title)
    : m_width(width), m_height(height)
{
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        std::exit(1);
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED); //SDL_RENDERER_PRESENTVSYNC fps
    if (!m_renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
        std::exit(1);
    }
}

Renderer::~Renderer() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window)   SDL_DestroyWindow(m_window);
}

void Renderer::clear(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(m_renderer, r,g,b,a);
    SDL_RenderClear(m_renderer);
}
void Renderer::fillRect(int x,int y,int w,int h,int r,int g,int b,int a) {
    SDL_Rect rc{ x,y,w,h };
    SDL_SetRenderDrawColor(m_renderer, r,g,b,a);
    SDL_RenderFillRect(m_renderer, &rc);
}
void Renderer::drawRect(int x,int y,int w,int h,int r,int g,int b,int a) {
    SDL_Rect rc{ x,y,w,h };
    SDL_SetRenderDrawColor(m_renderer, r,g,b,a);
    SDL_RenderDrawRect(m_renderer, &rc);
}
void Renderer::present() { SDL_RenderPresent(m_renderer); }
