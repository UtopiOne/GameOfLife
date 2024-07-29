#include "Grid.h"

#include "Config.h"
#include "Cell.h"

#include <raylib.h>
#include <raymath.h>

template<int width, int height>
void Grid<width, height>::Update() {
  Vector2 mousePos = GetMousePosition();
  m_SelectedTileX = (int)mousePos.x / CELL_WIDTH;
  m_SelectedTileY = (int)mousePos.y / CELL_HEIGHT;

  if (IsKeyPressed(KEY_R)) {
    ClearGrid();
    m_CurrentState = GridState::Editing;
  }

  switch (m_CurrentState) {
    case GridState::Editing: {
      UpdateEditing();
    } break;
    case GridState::Running: {
      UpdateRunning();
    } break;
    case GridState::Paused: {
      UpdatePaused();
    } break;
  }
}

template<int width, int height>
void Grid<width, height>::Draw() {
  DrawLine(0, 1, WIDTH, 1, GRAY);
  DrawLine(1, 0, 1, HEIGHT, GRAY);

  for (int x = 16; x <= WIDTH; x += CELL_WIDTH) {
    DrawLine(x, 0, x, HEIGHT, GRAY);
  }
  for (int y = 16; y <= HEIGHT; y += CELL_HEIGHT) {
    DrawLine(0, y, WIDTH, y, GRAY);
  }

  for (int x = 0; x <= width - 1; x++) {
    for (int y = 0; y <= height - 1; y++) {
      if (m_SelectedTileX == x && m_SelectedTileY == y) {
        DrawRectangle(x * 16, y * 16, CELL_WIDTH, CELL_HEIGHT, GRAY);
      }

      if (CellMatrix[x][y].State == CellState::Alive) {
        DrawRectangle(x * 16, y * 16, CELL_WIDTH, CELL_HEIGHT, WHITE);
      }
    }
  }

  if (m_CurrentState == GridState::Running) {
    int textSize = MeasureText("Running...", 40);
    DrawText("Running...", WIDTH / 2 - textSize / 2, 5, 40, RAYWHITE);
  }

  if (m_CurrentState == GridState::Editing) {
    int textSize = MeasureText("Editing. Press SPACE to run.", 40);
    DrawText("Editing. Press SPACE to run.", WIDTH / 2 - textSize / 2, 5, 40, RAYWHITE);
  }

  if (m_CurrentState == GridState::Paused) {
    int textSize = MeasureText("Paused", 40);
    DrawText("Paused", WIDTH / 2 - textSize / 2, 5, 40, RAYWHITE);
  }
}

template<int width, int height>
void Grid<width, height>::UpdateEditing() {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_MouseJustPressed) {
    if (CellMatrix[m_SelectedTileX][m_SelectedTileY].State == CellState::Dead) {
      CellMatrix[m_SelectedTileX][m_SelectedTileY].State = CellState::Alive;
      m_MouseJustPressed = true;
    } else {
      CellMatrix[m_SelectedTileX][m_SelectedTileY].State = CellState::Dead;
      m_MouseJustPressed = true;
    }
  }

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && m_MouseJustPressed) {
    m_MouseJustPressed = false;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    m_CurrentState = GridState::Running;
  }
}

template<int width, int height>
void Grid<width, height>::UpdateRunning() {
  if (IsKeyPressed(KEY_SPACE)) {
    m_CurrentState = GridState::Paused;
  }
}

template<int width, int height>
void Grid<width, height>::UpdatePaused() {
  if (IsKeyPressed(KEY_SPACE)) {
    m_CurrentState = GridState::Running;
  }
}

template<int width, int height>
int Grid<width, height>::GetNeighboring(int x, int y) {
}

template<int width, int height>
void Grid<width, height>::ClearGrid() {
  for (int x = 0; x <= width - 1; x++) {
    for (int y = 0; y <= height - 1; y++) {
      CellMatrix[x][y].State = CellState::Dead;
    }
  }
}