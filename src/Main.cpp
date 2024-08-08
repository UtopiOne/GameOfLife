#include <raylib.h>
#include <raymath.h>

#include "Config.h"

#include "Grid.cpp"
#include "Grid.h"

int main() {
  InitWindow(WIDTH, HEIGHT, "Conway's Game of Life");
  Image windowIcon = LoadImage("assets/icon.ico");
  SetWindowIcon(windowIcon);

  SetTargetFPS(60);

  Grid<WIDTH / CELL_WIDTH, HEIGHT / CELL_HEIGHT> grid;

  while (!WindowShouldClose()) {
    grid.Update();

    BeginDrawing();
    ClearBackground(BG_COLOR);
    grid.Draw();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
}
