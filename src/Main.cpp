#include <cstdio>
#include <raylib.h>
#include <raymath.h>

#include "Cell.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main() {
  InitWindow(WIDTH, HEIGHT, "Game of Life");

  SetTargetFPS(60);

  Cell grid[WIDTH / CELL_WIDTH][HEIGHT / CELL_HEIGHT];
  bool justPressed = false;

  while (!WindowShouldClose()) {
    Vector2 mousePos = GetMousePosition();
    int selected_tile_x = (int)mousePos.x / 16;
    int selected_tile_y = (int)mousePos.y / 16;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !justPressed) {
      if (grid[selected_tile_x][selected_tile_y].State == CellState::Dead) {
        grid[selected_tile_x][selected_tile_y].State = CellState::Alive;
        justPressed = true;
      } else {
        grid[selected_tile_x][selected_tile_y].State = CellState::Dead;
        justPressed = true;
      }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && justPressed) {
      justPressed = false;
    }

    BeginDrawing();
      ClearBackground(BLACK);

      for (int x = 0; x <= WIDTH / CELL_WIDTH; x++) {
        for (int y = 0; y <= HEIGHT / CELL_HEIGHT; y++) {
          if (selected_tile_x == x && selected_tile_y == y) {
            DrawRectangleLines(x * 16, y * 16, CELL_WIDTH, CELL_HEIGHT, GRAY);
          }

          if (grid[x][y].State == CellState::Alive) {
            DrawRectangle(x * 16, y * 16, CELL_WIDTH, CELL_HEIGHT, WHITE);
          }
        }
      }

      DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
}