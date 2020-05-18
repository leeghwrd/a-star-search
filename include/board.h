#ifndef BOARD_H
#define BOARD_H
#include "state.h"

class Board {

public:
    std::vector<std::vector<State>> ReadBoardFile(std::string path);
    void PrintBoard(const std::vector<std::vector<State>> board);

private:
    std::vector<State> ParseLine(std::string line);

};

#endif