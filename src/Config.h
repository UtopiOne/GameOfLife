#pragma once

// Width and height of game window
constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

// Width and height of a single cell
constexpr int CELL_WIDTH = 16;
constexpr int CELL_HEIGHT = 16;

// Amount of update cycles it takes before the screen updates
constexpr int SPEED = 5;

#define GRID_COLOR          DARKGRAY
#define HOVERED_CELL_COLOR  DARKGRAY
#define ALIVE_CELL_COLOR    WHITE
#define BG_COLOR            BLACK
#define TEXT_COLOR          RAYWHITE