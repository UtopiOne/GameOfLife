#include <raylib.h>
#include <raymath.h>

#include "Config.h"

#include "Grid.h"
#include "Grid.cpp"

int main() {
  InitWindow(WIDTH, HEIGHT, "Game of Life");

  SetTargetFPS(60);

  Grid<WIDTH / CELL_WIDTH, HEIGHT / CELL_HEIGHT> grid;

  while (!WindowShouldClose()) {
    grid.ProcessInput();

    BeginDrawing();
      ClearBackground(BLACK);

      grid.Draw();

      DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
}