#include <raylib.h>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main() {
  InitWindow(WIDTH, HEIGHT, "Game of Life");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    DrawFPS(0, 0);

    EndDrawing();
  }

  CloseWindow();  
}