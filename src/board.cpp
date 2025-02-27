/**
 * @file board.cpp
 * @brief Implementation of the board functions
 */

#include "board.hpp"
#include "consts.hpp"
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>
#include <iostream>

/**
 * @brief Converts a chess board position string (e.g., "a1") into row and column indices.
 *
 * @param position The position string consisting of a letter (column) and a number (row).
 * @return A pair of integers representing the row and column indices.
 * @throws std::invalid_argument If the input string is not exactly 2 characters long.
 * @throws std::out_of_range If the position is outside the valid board range.
 */
std::pair<int, int> stringToBoardPosition(const std::string& position) {
    if (position.length() != 2) {
        throw std::invalid_argument("Invalid position string");
    }

    char column = position[0];
    char row = position[1];

    if (column < 'a' || column > 'h' || row < '1' || row > '8') {
        throw std::out_of_range("Position out of range");
    }

    int columnIndex = column - 'a';
    int rowIndex = row - '1';

    return std::make_pair(rowIndex, columnIndex);
}

/**
 * @brief Converts a pair of row and column indices into a chess board position string.
 *
 * @param position A pair of integers representing the row and column indices.
 * @return A string representing the board position (e.g., "a1").
 */
std::string boardPositionToString(std::pair<int, int> position) {
    char column = position.second + 'a';
    char row = position.first + '1';
    return std::string(1, column) + std::string(1, row);
}

/**
 * @brief Modifies a bit on an 8x8 board represented by a 64-bit integer.
 *
 * @param board Pointer to the 64-bit integer representing the board.
 * @param row The row index (0-7).
 * @param column The column index (0-7).
 * @param value The boolean value to set (true for 1, false for 0).
 * @throws std::out_of_range If the row or column is out of bounds.
 */
void changeBitOnBoard(uint64_t* board, int row, int column, bool value) {
    if (row < 0 || row >= BOARD_LENGTH || column < 0 || column >= BOARD_LENGTH) {
        throw std::out_of_range("Position out of range");
    }

    int index = row * BOARD_LENGTH + column;
    uint64_t mask = 1ULL << index;

    if (value) {
        *board |= mask;
    } else {
        *board &= ~mask;
    }
}

/**
 * @brief Sets up the initial position of pieces on the board.
 *
 * @param white Pointer to the 64-bit integer representing the white pieces.
 * @param black Pointer to the 64-bit integer representing the black pieces.
 */
void setupInitialPos(uint64_t* white, uint64_t* black) {
    changeBitOnBoard(white, 3, 3, true);
    changeBitOnBoard(white, 4, 4, true);
    changeBitOnBoard(black, 3, 4, true);
    changeBitOnBoard(black, 4, 3, true);
}

/**
 * @brief Prints the board representation with both white and black pieces.
 *
 * @param white The 64-bit integer representing the white pieces.
 * @param black The 64-bit integer representing the black pieces.
 */
void printBoard(uint64_t white, uint64_t black) {
    // Print column labels
    std::cout << "  a b c d e f g h" << std::endl;

    for (int row = 0; row < BOARD_LENGTH; row++) {
        // Print row label
        std::cout << row + 1 << " ";

        for (int column = 0; column < BOARD_LENGTH; column++) {
            int index = row * BOARD_LENGTH + column;
            uint64_t mask = 1ULL << index;

            if (white & mask) {
                std::cout << "W ";
            } else if (black & mask) {
                std::cout << "B ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}


