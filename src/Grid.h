#pragma once

#include "Cell.h"

template<int width, int height>
class Grid {
public:
  Grid() {}
  ~Grid() {}

  void ProcessInput();
  void Draw();

  Cell CellMatrix[width][height];

private:
  bool m_MouseJustPressed = false;

  int m_SelectedTileX, m_SelectedTileY;
};