#pragma once
#include <deque>
#include <random>
#include "renderer.h"
#include "input.h"

struct Cell { int x,y; };
inline bool operator==(const Cell& a, const Cell& b){ return a.x==b.x && a.y==b.y; }

enum class StepResult { Moved, Ate, Died };

class SnakeGame {
public:
    SnakeGame(int gridW, int gridH, int cellPx);

    void reset();
    void handleKey(int sdlKeySym);
    void apply(Action a);
    StepResult updateTick(); 
    void render(Renderer& rnd) const;

    int score() const { return m_score; }

private:
    int m_gridW, m_gridH, m_cellPx;

    std::deque<Cell> m_snake;
    Cell m_dir{1,0};
    Cell m_desired{1,0};
    Cell m_apple{};
    int  m_score = 0;

    mutable std::mt19937 m_rng;
    Cell randCell() const;
    bool contains(const Cell& c) const;
};
