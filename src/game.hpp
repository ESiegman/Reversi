/**
 * @file game.hpp
 * @brief Header file for the game functions
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <utility>

/**
 * @class Game
 * @brief Manages the state and logic of a Reversi game, including player turns, move validation, and scoring.
 *
 */
class Game {
private:
    uint64_t white = 0;
    uint64_t black = 0;

public:
    void run();
    bool firstPlayer();
    void playerTurn(uint64_t &white, uint64_t &black, char player);
    std::pair<int,int> readMove(char player);
    bool checkValidMove(uint64_t white, uint64_t black, std::pair<int, int> boardPosition, char player);
    void applyMove(uint64_t &white, uint64_t &black, std::pair<int, int> boardPosition, char player);
    bool hasValidMoves(uint64_t white, uint64_t black, char player);
    std::pair<int, int> getScore(uint64_t white, uint64_t black);
};


#endif // GAME_HPP
