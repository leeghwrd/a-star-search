#include <vector>
#include <algorithm>
#include <string>
#include "cell.h"
#include "state.h"

/**
* std::sort the two-dimensional std::vector of ints in descending order.
*/
void Cell::CellSort(std::vector<std::vector<int>> *v)
{
    std::sort(v->begin(), v->end(), Compare);
}
/**
* Compare the F values of two cells.
*/

bool Cell::Compare(const std::vector<int> a, const std::vector<int> b)
{
    int f1 = a[2] + a[3]; // f1 = g1 + h1
    int f2 = b[2] + b[3]; // f2 = g2 + h2
    return f1 > f2;
}
/** 
 * Check that a cell is valid: on the grid, not an obstacle, and clear. 
 */
bool Cell::CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid)
{
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
}

std::string Cell::CellString(State cell)
{
  switch (cell)
  {
  case State::kObstacle:
    return "⛰️   ";
  case State::kPath:
    return "🚗   ";
  case State::kStart:
    return "🚦   ";
  case State::kFinish:
    return "🏁   ";

  default:
    return "-1   ";
  }
}
