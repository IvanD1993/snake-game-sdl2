#include "button.h"
#include "input.h"
#include "renderer.h"
#include "snake_game.h"
#include "text.h"
#include "time_utils.h"
#include <SDL.h>
#include <algorithm> // for std::max
#include <chrono>
#include <iostream>

struct Cadence {
    double stepAccum = 0.0;
    double stepInterval = 1.0 / 8.5;
    static constexpr double base = 1.0 / 8.5;
    static constexpr double min = 1.0 / 20.0;

    void reset() {
        stepAccum = 0.0;
        stepInterval = base;
    }
};

// small RAII for SDL
struct SDLGuard {
    SDLGuard() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
            std::cerr << "SDL_Init: " << SDL_GetError() << "\n";
            std::exit(1);
        }
    }
    ~SDLGuard() { SDL_Quit(); }
};

enum class State { Menu, Playing, Paused };

int run_app() {
    SDLGuard sdl_guard;

    // world units
    const int gridW = 32, gridH = 24, cellPx = 24;
    const int winW = gridW * cellPx, winH = gridH * cellPx;

    Renderer renderer(winW, winH, "snake (SDL2)");

    TextRenderer text;

    Button btnStart(winW / 2 - 140, winH / 2 - 40, 280, 80, "Start");
    Button btnResume(winW / 2 - 300, winH / 2 - 40, 240, 80, "Resume");
    Button btnQuit(winW / 2 + 60, winH / 2 - 40, 240, 80, "Quit");

    SnakeGame game(gridW, gridH, cellPx);

    Input input;
    Cadence cadence;
    // timing (engine update at 120 Hz)
    constexpr double hz = 120.0;
    constexpr double dt = 1.0 / hz;

    double accumulator = 0.0;

    int lastScore = 0;

    auto now = std::chrono::high_resolution_clock::now();
    auto seconds = [](auto d) { return std::chrono::duration<double>(d).count(); };

    State state = State::Menu;
    bool running = true;

    while (running) {
        // input
        InputFrame in = input.poll();

        // state machine actions
        if (state == State::Playing) {
            if (in.action == Action::PauseToggle)
                state = State::Paused;
            else if (in.action == Action::Reset) {
                game.reset();
                cadence.reset();
                lastScore = 0;
            } else
                game.apply(in.action);
        } else if (state == State::Menu) {
            if (btnStart.update(in.mouseDown, in.clicked, in.mouseX, in.mouseY)) {
                game.reset();
                cadence.reset();
                lastScore = 0;
                state = State::Playing;
            }
        } else if (state == State::Paused) {
            if (in.action == Action::PauseToggle)
                state = State::Playing;
            bool resume = btnResume.update(in.mouseDown, in.clicked, in.mouseX, in.mouseY);
            bool quit = btnQuit.update(in.mouseDown, in.clicked, in.mouseX, in.mouseY);
            if (resume)
                state = State::Playing;
            if (quit)
                running = false;
        }

        // fixed update
        auto newNow = std::chrono::high_resolution_clock::now();
        accumulator += seconds(newNow - now);
        now = newNow;
        if (accumulator > 0.25)
            accumulator = 0.25;

        while (accumulator >= dt) {
            accumulator -= dt;
            if (state == State::Playing) {
                cadence.stepAccum += dt;
                while (cadence.stepAccum >= cadence.stepInterval) {
                    cadence.stepAccum -= cadence.stepInterval;
                    StepResult res = game.updateTick();
                    if (res == StepResult::Died) {
                        cadence.reset();
                        lastScore = 0;
                    } else if (res == StepResult::Ate) {
                        int s = game.score();
                        if (s != lastScore && s % 50 == 0) {
                            cadence.stepInterval =
                                std::max(Cadence::min, cadence.stepInterval * 0.9);
                        }
                        lastScore = s;
                    }
                }
            }
        }

        // render
        renderer.clear(24, 26, 30);
        game.render(renderer);
        if (state == State::Menu) {
            // dim background
            renderer.fillRect(0, 0, renderer.width(), renderer.height(), 0, 0, 0, 140);
            // button + label
            btnStart.draw(renderer);
            btnStart.drawText(renderer.raw(), text);
        } else if (state == State::Paused) {
            renderer.fillRect(0, 0, renderer.width(), renderer.height(), 0, 0, 0, 160);
            btnResume.draw(renderer);
            btnQuit.draw(renderer);
            btnResume.drawText(renderer.raw(), text);
            btnQuit.drawText(renderer.raw(), text);
        }
        renderer.present();
    }

    return 0;
}
