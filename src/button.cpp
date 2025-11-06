#include "button.h"
#include <SDL.h>

static bool pointInRect(int mx,int my,int x,int y,int w,int h){
    return mx>=x && mx<x+w && my>=y && my<y+h;
}

Button::Button(int x,int y,int w,int h,std::string label)
: x(x), y(y), w(w), h(h), label(std::move(label)) {}

bool Button::update(bool mouseDown, bool mouseClicked, int mx, int my) {
    hovered = pointInRect(mx,my,x,y,w,h);
    pressed = hovered && mouseDown;
    return hovered && mouseClicked;
}

void Button::draw(Renderer& rnd) const {
    int r=70,g=100,b=200;
    if (pressed)      { r=60; g=85; b=170; }
    else if (hovered) { r=90; g=130; b=235; }
    rnd.fillRect(x,y,w,h, r,g,b);
    rnd.drawRect(x,y,w,h, 20,30,50);
}

void Button::drawText(SDL_Renderer* sdl, TextRenderer& font) const {
    SDL_Color white{255,255,255,255};

    int tx = x + w/2 - 40; // quick centering approximation
    int ty = y + h/2 - 18;

    font.draw(sdl, label, tx, ty, white);
}
