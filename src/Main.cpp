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

    for (int i = 0; i <= WIDTH; i += 16) {
      DrawLine(i, 0, i, HEIGHT, GRAY);
    }

    for (int i = 0; i <= HEIGHT; i += 16) {
      DrawLine(0, i, WIDTH, i, GRAY);
    }

    EndDrawing();
  }

  CloseWindow();
}