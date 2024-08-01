#include "Grid.h"

#include "Config.h"
#include "Cell.h"

#include <raylib.h>
#include <raymath.h>

template<int width, int height>
void Grid<width, height>::Update() {
  Vector2 mousePos = GetMousePosition();
  m_SelectedTileX = static_cast<int>(mousePos.x) / CELL_WIDTH;
  m_SelectedTileY = static_cast<int>(mousePos.y) / CELL_HEIGHT;

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
  DrawLine(0, 1, WIDTH, 1, GRID_COLOR);
  DrawLine(1, 0, 1, HEIGHT, GRID_COLOR);

  for (int x = 16; x <= WIDTH; x += CELL_WIDTH) {
    DrawLine(x, 0, x, HEIGHT, GRID_COLOR);
  }
  for (int y = 16; y <= HEIGHT; y += CELL_HEIGHT) {
    DrawLine(0, y, WIDTH, y, GRID_COLOR);
  }

  for (int x = 0; x <= width; x++) {
    for (int y = 0; y <= height; y++) {
      if (m_SelectedTileX == x && m_SelectedTileY == y) {
        DrawRectangle(x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, HOVERED_CELL_COLOR);
      }

      if (CellMatrix[x][y].IsAlive) {
        DrawRectangle(x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, ALIVE_CELL_COLOR);
      }
    }
  }

  if (m_CurrentState == GridState::Running) {
    int textSize = MeasureText("Running...", 40);
    int genSize = MeasureText(TextFormat("Generation: %i", m_Generation), 20);
    DrawText("Running...", WIDTH / 2 - textSize / 2, 5, 40, TEXT_COLOR);
    DrawText(TextFormat("Generation: %i", m_Generation), WIDTH / 2 - genSize / 2, 60, 20, TEXT_COLOR);
  }

  if (m_CurrentState == GridState::Editing) {
    int textSize = MeasureText("Editing. Press SPACE to run.", 40);
    DrawText("Editing. Press SPACE to run.", WIDTH / 2 - textSize / 2, 5, 40, TEXT_COLOR);
  }

  if (m_CurrentState == GridState::Paused) {
    int textSize = MeasureText("Paused", 40);
    int genSize = MeasureText(TextFormat("Generation: %i", m_Generation), 20);
    DrawText("Paused", WIDTH / 2 - textSize / 2, 5, 40, TEXT_COLOR);
    DrawText(TextFormat("Generation: %i", m_Generation), WIDTH / 2 - genSize / 2, 60, 20, TEXT_COLOR);
  }
}

template<int width, int height>
void Grid<width, height>::UpdateEditing() {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_MouseJustPressed) {
    CellMatrix[m_SelectedTileX][m_SelectedTileY].IsAlive = !CellMatrix[m_SelectedTileX][m_SelectedTileY].IsAlive;
    m_MouseJustPressed = true;
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
  if (m_Frame % SPEED == 0) {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int neighboring = GetNeighboring(x, y);

        if (neighboring < 2 || neighboring > 3) {
          CellMatrix[x][y].IsAliveNextGeneration = false;
        } else if (neighboring == 3) {
          CellMatrix[x][y].IsAliveNextGeneration = true;
        } else {
          CellMatrix[x][y].IsAliveNextGeneration = CellMatrix[x][y].IsAlive;
        }
      }
    }

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        CellMatrix[x][y].IsAlive = CellMatrix[x][y].IsAliveNextGeneration;
      }
    }

    m_Generation++;
  }

  m_Frame++;

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
  int neighboring = 0;

  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (i == width && CellMatrix[0][j].IsAlive && !(i == x && j == y)) {
        neighboring++;
      } else if (i == -1 && CellMatrix[width - 1][j].IsAlive && !(i == x && j == y)) {
        neighboring++;
      } else if (j == -1 && CellMatrix[i][height - 1].IsAlive && !(i == x && j == y)) {
        neighboring++;
      } else if (j == height && CellMatrix[i][0].IsAlive && !(i == x && j == y)) {
        neighboring++;
      } else if (CellMatrix[i][j].IsAlive && !(i == x && j == y) && i != width && i != -1 && j != height && j != -1) {
        neighboring++;
      }
    }
  }

  return neighboring;
}

template<int width, int height>
void Grid<width, height>::ClearGrid() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      CellMatrix[x][y].IsAlive = false;
    }
  }
  m_Generation = 0;
}