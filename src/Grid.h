#pragma once

#include "Cell.h"

enum class GridState {
  // Editing initial state
  Editing,
  Running,
  Paused,
};

template<int width, int height>
class Grid {
public:
  Grid() {}
  ~Grid() {}

  void Update();
  void Draw();

  Cell CellMatrix[width][height];

private:
  bool m_MouseJustPressed = false;
  GridState m_CurrentState = GridState::Editing;

  int m_SelectedTileX, m_SelectedTileY;
  int m_Generation = 0;
  int m_Frame = 1;

  void UpdateEditing();
  void UpdateRunning();
  void UpdatePaused();

  int GetNeighboring(int x, int y);
  void ClearGrid();
};