#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <cstdint>

std::pair<int, int> stringToBoardPosition(const std::string& position);
void changeBitOnBoard(uint64_t* board, int row, int column, bool value);
void setupInitialPos(uint64_t* white, uint64_t* black);
void printBoard(uint64_t white, uint64_t black);

#endif // BOARD_HPP


