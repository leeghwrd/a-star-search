#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "cell.h"
#include "state.h"
#include "board.h"

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
  return std::abs(x2 - x1) + std::abs(y2 - y1);
}



/** 
 * Add a node to the open list and mark it as open. 
 */
void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>> &grid)
{
  // Add node to open std::vector, and mark grid cell as closed.
  openlist.push_back(std::vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

/** 
 * Expand current nodes's neighbors and add them to the open list.
 */

void ExpandNeighbors(const std::vector<int> &current, int goal[2], std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>> &grid)
{
  // Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++)
  {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (Cell::CheckValidCell(x2, y2, grid))
    {
      // Increment g value, compute h value, and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
}

/** 
 * Implementation of A* search algorithm
 */
std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int init[2], int goal[2])
{
  // Create the std::vector of open nodes.
  std::vector<std::vector<int>> open{};

  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, open, grid);

  while (open.size() > 0)
  {
    // Get the next node
    Cell::CellSort(&open);
    auto current = open.back();
    open.pop_back();
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;

    // Check if we're done.
    if (x == goal[0] && y == goal[1])
    {
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kFinish;

      return grid;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal, open, grid);
  }

  // We've run out of new nodes to explore and haven't found a path.
  std::cout << "No path found!"
            << "\n";
  return std::vector<std::vector<State>>{};
}


int main()
{
  Board new_board;
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = new_board.ReadBoardFile("../boards/1.board");
  auto solution = Search(board, init, goal);
  new_board.PrintBoard(solution);
}