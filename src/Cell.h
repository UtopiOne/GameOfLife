#pragma once

constexpr int CELL_WIDTH = 16;
constexpr int CELL_HEIGHT = 16;

enum class CellState {
    Dead,
    Alive
};

struct Cell {
    CellState State = CellState::Dead;
};