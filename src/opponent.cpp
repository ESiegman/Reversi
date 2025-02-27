/**
 * @file opponent.cpp
 * @brief This file contains the implementation of the Opponent class.
 */

#include "opponent.hpp"
#include "game.hpp"
#include "consts.hpp"
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
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @return A pair of integers representing the score of the best move and the row and column of the move.
 */
std::pair<int, std::pair<int, int>> Opponent::minimax(Game& gameInstance, uint64_t white, uint64_t black, char player, int depth, bool isMaximizing, int alpha, int beta) {
    if (depth == 0 || !gameInstance.hasValidMoves(white, black, player)) { 
        return {evaluateBoard(gameInstance, white, black, player), {-1, -1}}; // Use the new evaluation function
    }

    std::pair<int, int> bestMove = {-1, -1}; // Initialize best move

    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (auto move : getPossibleMoves(gameInstance, white, black, player)) {
            uint64_t newWhite = white, newBlack = black;
            gameInstance.applyMove(newWhite, newBlack, move, player);
            int eval = minimax(gameInstance, newWhite, newBlack, opponent(player), depth - 1, false, alpha, beta).first;
            if (eval > maxEval) {
                maxEval = eval;
                bestMove = move;
            }
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return {maxEval, bestMove};
    } else {
        int minEval = INT_MAX;
        for (auto move : getPossibleMoves(gameInstance, white, black, player)) {
            uint64_t newWhite = white, newBlack = black;
            gameInstance.applyMove(newWhite, newBlack, move, player);
            int eval = minimax(gameInstance, newWhite, newBlack, opponent(player), depth - 1, true, alpha, beta).first;
            if (eval < minEval) {
                minEval = eval;
                bestMove = move;
            }
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return {minEval, bestMove};
    }
}

/**
 * @brief Evaluates the board state with additional scoring for corners, sides, and mobility.
 *
 * @param gameInstance The current game instance.
 * @param white The bitboard representing the white player's pieces.
 * @param black The bitboard representing the black player's pieces.
 * @param player The current player ('W' for white, 'B' for black).
 * @return The evaluated score of the board.
 */
int Opponent::evaluateBoard(Game& gameInstance, uint64_t white, uint64_t black, char player) {
    auto score = gameInstance.getScore(white, black);
    int playerScore = (player == 'W') ? score.first : score.second;
    int opponentScore = (player == 'W') ? score.second : score.first;

    // Corner positions
    const std::vector<std::pair<int, int>> corners = {{0, 0}, {0, BOARD_LENGTH - 1}, {BOARD_LENGTH - 1, 0}, {BOARD_LENGTH - 1, BOARD_LENGTH - 1}};

        // Calculate corner and side control
    int cornerControl = 0;
    int sideControl = 0;

    // Calculate corner control
    for (const auto& corner : corners) {
        int bitPosition = corner.first * BOARD_LENGTH + corner.second;
        if ((player == 'W' && (white & (1ULL << bitPosition))) ||
            (player == 'B' && (black & (1ULL << bitPosition)))) {
            cornerControl += CORNER_WEIGHT;
        } else if ((player == 'W' && (black & (1ULL << bitPosition))) ||
                   (player == 'B' && (white & (1ULL << bitPosition)))) {
            cornerControl -= CORNER_WEIGHT;
        }
    }
    for (int i = 1; i < BOARD_LENGTH - 1; ++i) {
        int topBit = i;
        int bottomBit = (BOARD_LENGTH - 1) * BOARD_LENGTH + i;
        int leftBit = i * BOARD_LENGTH;
        int rightBit = i * BOARD_LENGTH + (BOARD_LENGTH - 1);

        if ((player == 'W' && ((white & (1ULL << topBit)) || (white & (1ULL << leftBit)) || (white & (1ULL << bottomBit)) || (white & (1ULL << rightBit)))) ||
            (player == 'B' && ((black & (1ULL << topBit)) || (black & (1ULL << leftBit)) || (black & (1ULL << bottomBit)) || (black & (1ULL << rightBit))))) {
            sideControl += SIDE_WEIGHT;
        } else if ((player == 'W' && ((black & (1ULL << topBit)) || (black & (1ULL << leftBit)) || (black & (1ULL << bottomBit)) || (black & (1ULL << rightBit)))) ||
                   (player == 'B' && ((white & (1ULL << topBit)) || (white & (1ULL << leftBit)) || (white & (1ULL << bottomBit)) || (white & (1ULL << rightBit))))) {
            sideControl -= SIDE_WEIGHT;
        }
    }

    // Mobility
    int playerMoves = getPossibleMoves(gameInstance, white, black, player).size();
    int opponentMoves = getPossibleMoves(gameInstance, white, black, opponent(player)).size();
    int mobility = (playerMoves - opponentMoves) / 5;

    // Total evaluation
    return playerScore - opponentScore + cornerControl + sideControl + mobility;
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

    for (int row = 0; row < BOARD_LENGTH; ++row) {
        for (int col = 0; col < BOARD_LENGTH; ++col) {
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


