#include "text.h"
#include <iostream>

TextRenderer::TextRenderer() {
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << "\n";
        std::exit(1);
    }

    m_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 32);
    if (!m_font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << "\n";
        std::exit(1);
    }
}

TextRenderer::~TextRenderer() {
    if (m_font) TTF_CloseFont(m_font);
    TTF_Quit();
}

void TextRenderer::draw(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surf = TTF_RenderUTF8_Blended(m_font, text.c_str(), color);
    SDL_Texture* tex  = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_Rect dest{ x, y, surf->w, surf->h };
    SDL_RenderCopy(renderer, tex, nullptr, &dest);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}
