/**
 * @file opponent.hpp
 * @brief This file contains the class definition for the Opponent class.
 */

#ifndef OPPONENT_HPP
#define OPPONENT_HPP

#include "game.hpp"
#include <vector>
#include <utility>
#include <cstdint>

/**
 * @class Opponent
 * @brief Represents an opponent in the game, providing methods to determine valid moves and evaluate game states.
 *  
 */
class Opponent {
public:
    std::pair<int, std::pair<int, int>> minimax(Game& gameInstance, uint64_t white, uint64_t black, char player, int depth, bool isMaximizing, int alpha, int beta);
    std::vector<std::pair<int, int>> getPossibleMoves(Game& gameInstance, uint64_t white, uint64_t black, char player);
    char opponent(char player);
    int evaluateBoard(Game& gameInstance, uint64_t white, uint64_t black, char player);
};

#endif
