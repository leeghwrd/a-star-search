
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "board.h"
#include "state.h"
#include "cell.h"

std::vector<State> Board::ParseLine(std::string line)
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

std::vector<std::vector<State>> Board::ReadBoardFile(std::string path)
{
  std::ifstream myfile(path);
  std::vector<std::vector<State>> board{};
  if (myfile)
  {
    std::string line;
    while (getline(myfile, line))
    {
      std::vector<State> row = Board::ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}


void Board::PrintBoard(const std::vector<std::vector<State>> board)
{
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      std::cout << Cell::CellString(board[i][j]);
    }
    std::cout << "\n";
  }
}