#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class State
{
  kEmpty,
  kObstacle,
  kClosed,
  kPath,
  kStart,
  kFinish
};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::vector<State> ParseLine(std::string line)
{
  std::stringstream sline(line);
  int n;
  char c;
  std::vector<State> row;
  while (sline >> n >> c && c == ',')
  {
    if (n == 0)
    {
      row.push_back(State::kEmpty);
    }
    else
    {
      row.push_back(State::kObstacle);
    }
  }
  return row;
}

std::vector<std::vector<State>> ReadBoardFile(std::string path)
{
  std::ifstream myfile(path);
  std::vector<std::vector<State>> board{};
  if (myfile)
  {
    std::string line;
    while (getline(myfile, line))
    {
      std::vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

/**
 * Compare the F values of two cells.
 */
bool Compare(const std::vector<int> a, const std::vector<int> b)
{
  int f1 = a[2] + a[3]; // f1 = g1 + h1
  int f2 = b[2] + b[3]; // f2 = g2 + h2
  return f1 > f2;
}

/**
 * std::sort the two-dimensional std::vector of ints in descending order.
 */
void CellSort(std::vector<std::vector<int>> *v)
{
  std::sort(v->begin(), v->end(), Compare);
}

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
  return std::abs(x2 - x1) + std::abs(y2 - y1);
}

/** 
 * Check that a cell is valid: on the grid, not an obstacle, and clear. 
 */
bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid)
{
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
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
    if (CheckValidCell(x2, y2, grid))
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
    CellSort(&open);
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

std::string CellString(State cell)
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

void PrintBoard(const std::vector<std::vector<State>> board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      std::cout << CellString(board[i][j]);
    }
    std::cout << "\n";
  }
}

int main()
{
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("boards/1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
}