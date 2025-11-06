#include "snake_game.h"
#include <SDL.h>
#include <iostream>
#include <random>

SnakeGame::SnakeGame(int gridW,int gridH,int cellPx)
: m_gridW(gridW), m_gridH(gridH), m_cellPx(cellPx), m_rng(std::random_device{}())
{
    reset();
}

void SnakeGame::reset() {
    m_snake = { {m_gridW/2, m_gridH/2}, {m_gridW/2-1, m_gridH/2}, {m_gridW/2-2, m_gridH/2} };
    m_dir = {1,0};
    m_desired = m_dir;
    m_score = 0;                                  // keep score reset
    m_apple = randCell(); while (contains(m_apple)) m_apple = randCell();
    std::cout << "Reset. Score=0\n";
}

Cell SnakeGame::randCell() const {
    std::uniform_int_distribution<int> X(0, m_gridW-1), Y(0, m_gridH-1);
    return Cell{ X(m_rng), Y(m_rng) };
}
bool SnakeGame::contains(const Cell& c) const {
    for (auto& s : m_snake) if (s==c) return true;
    return false;
}

void SnakeGame::handleKey(int key) {
    switch (key) {
        case SDLK_LEFT:  if (m_dir.x != 1)  m_desired = {-1,0}; break;
        case SDLK_RIGHT: if (m_dir.x != -1) m_desired = { 1,0}; break;
        case SDLK_UP:    if (m_dir.y != 1)  m_desired = { 0,-1}; break;
        case SDLK_DOWN:  if (m_dir.y != -1) m_desired = { 0,1}; break;
    }
}

void SnakeGame::apply(Action a) {
    switch (a) {
        case Action::Left:  if (m_dir.x != 1)  m_desired = {-1,0}; break;
        case Action::Right: if (m_dir.x != -1) m_desired = { 1,0}; break;
        case Action::Up:    if (m_dir.y != 1)  m_desired = { 0,-1}; break;
        case Action::Down:  if (m_dir.y != -1) m_desired = { 0,1}; break;
        default: break;
    }
}

StepResult SnakeGame::updateTick() {
    m_dir = m_desired;

    Cell head = m_snake.front();
    Cell next{ head.x + m_dir.x, head.y + m_dir.y };

    // wall collisions
    if (next.x < 0 || next.x >= m_gridW || next.y < 0 || next.y >= m_gridH) {
        std::cout << "Hit wall. Final score: " << m_score << "\n";
        reset();
        return StepResult::Died;
    }
    // self collisions
    if (contains(next)) {
        std::cout << "Hit self. Final score: " << m_score << "\n";
        reset();
        return StepResult::Died;
    }

    m_snake.push_front(next);
    if (next == m_apple) {
        m_score += 10;
        do { m_apple = randCell(); } while (contains(m_apple));
        std::cout << "Score: " << m_score << "\n";
        return StepResult::Ate;
    } else {
        m_snake.pop_back();
        return StepResult::Moved;
    }
}

void SnakeGame::render(Renderer& rnd) const {
    // apple
    rnd.fillRect(m_apple.x * m_cellPx, m_apple.y * m_cellPx, m_cellPx, m_cellPx, 220,70,70);

    // snake
    int i=0;
    for (auto& s : m_snake) {
        int x = s.x * m_cellPx, y = s.y * m_cellPx;
        if (i++==0) rnd.fillRect(x,y,m_cellPx,m_cellPx, 120,220,120);
        else        rnd.fillRect(x,y,m_cellPx,m_cellPx,  90,190, 90);
    }
}
