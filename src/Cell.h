#pragma once

enum class CellState {
    Dead,
    Alive
};

struct Cell {
    CellState State = CellState::Dead;
};