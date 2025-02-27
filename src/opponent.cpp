/**
 * @file opponent.cpp
 * @brief This file contains the implementation of the Opponent class.
 */

#include "opponent.hpp"
#include "game.hpp" 
#include <climits>
#include <vector>


/**
 * @brief Implements the minimax algorithm to evaluate the best move for a player.
 *
 * This function recursively evaluates the game tree to determine the optimal move
 * for the current player using the minimax algorithm. It considers all possible moves,
 * applies them, and evaluates the resulting game state.
 *
 * @param gameInstance The current game instance.
 * @param white The bitboard representing the white player's pieces.
 * @param black The bitboard representing the black player's pieces.
 * @param player The current player ('W' for white, 'B' for black).
 * @param depth The depth of the search tree.
 * @param isMaximizing A boolean indicating if the current player is maximizing or minimizing.
 * @return A pair of integers representing the score of the best move and the row and column of the move.
 */
std::pair<int, std::pair<int, int>> Opponent::minimax(Game& gameInstance, uint64_t white, uint64_t black, char player, int depth, bool isMaximizing) {
    if (depth == 0 || !gameInstance.hasValidMoves(white, black, player)) { 
        auto score = gameInstance.getScore(white, black);
        return {score.first - score.second, {-1, -1}}; // Return a dummy move when depth is 0
    }

    std::pair<int, int> bestMove = {-1, -1}; // Initialize best move

    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (auto move : getPossibleMoves(gameInstance, white, black, player)) {
            uint64_t newWhite = white, newBlack = black;
            gameInstance.applyMove(newWhite, newBlack, move, player);
            int eval = minimax(gameInstance, newWhite, newBlack, opponent(player), depth - 1, false).first;
            if (eval > maxEval) {
                maxEval = eval;
                bestMove = move;
            }
        }
        return {maxEval, bestMove};
    } else {
        int minEval = INT_MAX;
        for (auto move : getPossibleMoves(gameInstance, white, black, player)) {
            uint64_t newWhite = white, newBlack = black;
            gameInstance.applyMove(newWhite, newBlack, move, player);
            int eval = minimax(gameInstance, newWhite, newBlack, opponent(player), depth - 1, true).first;
            if (eval < minEval) {
                minEval = eval;
                bestMove = move;
            }
        }
        return {minEval, bestMove};
    }
}


/**
 * @brief Retrieves all possible valid moves for the current player.
 *
 * This function iterates over the board and checks each position to determine
 * if placing a piece there is a valid move for the current player.
 *
 * @param gameInstance The current game instance.
 * @param white The bitboard representing the white player's pieces.
 * @param black The bitboard representing the black player's pieces.
 * @param player The current player ('W' for white, 'B' for black).
 * @return A vector of pairs representing the row and column of each valid move.
 */
std::vector<std::pair<int, int>> Opponent::getPossibleMoves(Game& gameInstance, uint64_t white, uint64_t black, char player) {
    std::vector<std::pair<int, int>> possibleMoves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::pair<int, int> boardPosition = {row, col};
            if (gameInstance.checkValidMove(white, black, boardPosition, player)) {
                possibleMoves.push_back(boardPosition);
            }
        }
    }
    return possibleMoves;
}


/**
 * @brief Determines the opponent of the current player.
 *
 * This function returns the character representing the opponent of the current player.
 *
 * @param player The current player ('W' for white, 'B' for black).
 * @return The character representing the opponent ('B' for white, 'W' for black).
 */
char Opponent::opponent(char player) {
    return (player == 'W') ? 'B' : 'W';
}


