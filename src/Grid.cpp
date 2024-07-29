#include "Grid.h"

#include "Config.h"
#include "Cell.h"

#include <raylib.h>
#include <raymath.h>

template<int width, int height>
void Grid<width, height>::ProcessInput() {
    Vector2 mousePos = GetMousePosition();
    m_SelectedTileX = (int)mousePos.x / 16;
    m_SelectedTileY = (int)mousePos.y / 16;

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
}

template<int width, int height>
void Grid<width, height>::Draw() {
  for (int x = 0; x <= width; x++) {
    for (int y = 0; y <= height; y++) {
      if (m_SelectedTileX == x && m_SelectedTileY == y) {
        DrawRectangleLines(x * 16, y * 16, CELL_WIDTH, CELL_HEIGHT, GRAY);
      }

      if (CellMatrix[x][y].State == CellState::Alive) {
        DrawRectangle(x * 16, y * 16, CELL_WIDTH, CELL_HEIGHT, WHITE);
      }
    }
  }
}