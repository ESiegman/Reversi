#include "game.hpp"
#include "board.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void Game::run() {
    setupInitialPos(&white, &black);
    
    if (firstPlayer()) {
        playerTurn(white, black, 'W');
    } 

    while (hasValidMoves(white, black, 'W') || hasValidMoves(white, black, 'B')) {
        playerTurn(white, black, 'B');
    }

    std::pair<int, int> score = getScore(white, black);
    std::cout << "Game over" << std::endl;
    std::cout << "White: " << score.first << " Black: " << score.second << std::endl;
    if (score.first > score.second) {
        std::cout << "White wins" << std::endl;
    } else if (score.first < score.second) {
        std::cout << "Black wins" << std::endl;
    } else {
        std::cout << "It's a tie" << std::endl;
    }
}

bool Game::firstPlayer() {
    srand(time(0));
    return rand() % 2 == 0;
}

void Game::playerTurn(uint64_t &white, uint64_t &black, char player) {
    printBoard(white, black);

    if (!hasValidMoves(white, black, player)) {
        std::cout << player << " has no valid moves" << std::endl;
        return;
    }

    printf("%c's turn: ", player);

    std::pair<int, int> boardPosition = readMove(player);
    applyMove(white, black, boardPosition, player);
}

std::pair<int,int> Game::readMove(char player) {
    std::string position;
    std::cin >> position;

    std::pair<int, int> boardPosition = stringToBoardPosition(position);

    if (!checkValidMove(white, black, boardPosition, player)) {
        std::cout << "Invalid move" << std::endl;
        return readMove(player);
    }

    return boardPosition;
}

bool Game::checkValidMove(uint64_t white, uint64_t black, std::pair<int, int> boardPosition, char player) {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    uint64_t playerBoard = (player == 'W') ? white : black;
    uint64_t opponentBoard = (player == 'W') ? black : white;

    int row = boardPosition.first;
    int column = boardPosition.second;
    int index = row * 8 + column;
    uint64_t mask = 1ULL << index;

    if ((playerBoard & mask) || (opponentBoard & mask)) {
        return false; // The position is already occupied
    }

    for (auto& direction : directions) {
        int dRow = direction[0];
        int dCol = direction[1];
        int r = row + dRow;
        int c = column + dCol;
        bool hasOpponentBetween = false;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            int currentIndex = r * 8 + c;
            uint64_t currentMask = 1ULL << currentIndex;

            if (opponentBoard & currentMask) {
                hasOpponentBetween = true;
            } else if (playerBoard & currentMask) {
                if (hasOpponentBetween) {
                    return true; // Valid move found
                }
                break;
            } else {
                break;
            }

            r += dRow;
            c += dCol;
        }
    }

    return false; // No valid move found
}

void Game::applyMove(uint64_t &white, uint64_t &black, std::pair<int, int> boardPosition, char player) {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    uint64_t playerBoard = (player == 'W') ? white : black;
    uint64_t opponentBoard = (player == 'W') ? black : white;

    int row = boardPosition.first;
    int column = boardPosition.second;
    int index = row * 8 + column;
    uint64_t mask = 1ULL << index;

    // Place the player's piece on the board
    playerBoard |= mask;

    for (auto& direction : directions) {
        int dRow = direction[0];
        int dCol = direction[1];
        int r = row + dRow;
        int c = column + dCol;
        bool hasOpponentBetween = false;
        std::vector<int> toFlip;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            int currentIndex = r * 8 + c;
            uint64_t currentMask = 1ULL << currentIndex;

            if (opponentBoard & currentMask) {
                hasOpponentBetween = true;
                toFlip.push_back(currentIndex);
            } else if (playerBoard & currentMask) {
                if (hasOpponentBetween) {
                    // Flip the opponent's pieces
                    for (int flipIndex : toFlip) {
                        uint64_t flipMask = 1ULL << flipIndex;
                        opponentBoard &= ~flipMask;
                        playerBoard |= flipMask;
                    }
                }
                break;
            } else {
                break;
            }

            r += dRow;
            c += dCol;
        }
    }

    // Update the boards
    if (player == 'W') {
        white = playerBoard;
        black = opponentBoard;
    } else {
        black = playerBoard;
        white = opponentBoard;
    }
}

bool Game::hasValidMoves(uint64_t white, uint64_t black, char player) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::pair<int, int> boardPosition = {row, col};
            if (checkValidMove(white, black, boardPosition, player)) {
                return true;
            }
        }
    }
    return false;
}

std::pair<int, int> Game::getScore(uint64_t white, uint64_t black) {
    int whiteCount = __builtin_popcountll(white);
    int blackCount = __builtin_popcountll(black);
    return {whiteCount, blackCount};
}

