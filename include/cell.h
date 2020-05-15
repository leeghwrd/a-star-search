#ifndef CELL_H
#define CELL_H

#include <vector>
#include <algorithm>
#include "state.h"

class Cell
{
public:
    /**
    * std::sort the two-dimensional std::vector of ints in descending order.
    */
    static void CellSort(std::vector<std::vector<int>> *v);
    /**
    * Compare the F values of two cells.
    */
    /** 
    * Check that a cell is valid: on the grid, not an obstacle, and clear. 
    */
    static bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid);
    
    static std::string CellString(State cell);

private:
    static bool Compare(const std::vector<int> a, const std::vector<int> b);
};

#endif