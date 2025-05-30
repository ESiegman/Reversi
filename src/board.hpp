/**
 * @file board.hpp
 * @brief Header file for the board functions
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <cstdint>

std::pair<int, int> stringToBoardPosition(const std::string& position);
std::string boardPositionToString(std::pair<int, int> position);
void changeBitOnBoard(uint64_t* board, int row, int column, bool value);
void setupInitialPos(uint64_t* white, uint64_t* black);
void printBoard(uint64_t white, uint64_t black);

#endif // BOARD_HPP


