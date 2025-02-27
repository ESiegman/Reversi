#include "board.hpp"

#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>
#include <iostream>

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

void changeBitOnBoard(uint64_t* board, int row, int column, bool value) {
    if (row < 0 || row >= 8 || column < 0 || column >= 8) {
        throw std::out_of_range("Position out of range");
    }

    int index = row * 8 + column;
    uint64_t mask = 1ULL << index;

    if (value) {
        *board |= mask;
    } else {
        *board &= ~mask;
    }
}

void setupInitialPos(uint64_t* white, uint64_t* black) {
    changeBitOnBoard(white, 3, 3, true);
    changeBitOnBoard(white, 4, 4, true);
    changeBitOnBoard(black, 3, 4, true);
    changeBitOnBoard(black, 4, 3, true);
}

void printBoard(uint64_t white, uint64_t black) {
    // Print column labels
    std::cout << "  a b c d e f g h" << std::endl;

    for (int row = 0; row < 8; row++) {
        // Print row label
        std::cout << row + 1 << " ";

        for (int column = 0; column < 8; column++) {
            int index = row * 8 + column;
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


