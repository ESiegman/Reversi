# Reversi

## Overview
Reversi is a strategy board game for two players, played on an 8×8 uncheckered board. The game pieces have a light and a dark face, each side representing one player. The objective of the game is to have the majority of discs turned to display your color when the last playable empty square is filled.

## Build Instructions
To build and run the Reversi game, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/ESiegman/Reversi.git
    cd Reversi
    ```
    
2. If you are using NixOS, enter the development environment:
    ```sh
    nix develop
    ```
    
3. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```

4. Generate build files using CMake:
    ```sh
    cmake ..
    ```

5. Build the project:
    ```sh
    cmake --build .
    ```

6. Run the executable:
    ```sh
    ./Reversi
    ```

## Gameplay Instructions
When the game starts, you will be prompted to enter coordinates such as `a4` or `e7` depending on where you want to place your piece.

### General Rules of Reversi
- The game begins with two black discs and two white discs placed in the center of the board in a diagonal pattern.
- The first player is determined at random.
- Players take turns placing discs on the board with their assigned color facing up.
- A valid move must outflank one or more of the opponent's discs in a straight line (horizontally, vertically, or diagonally).
- Outflanked discs are flipped to the current player's color.
- If a player cannot make a valid move, they must pass their turn.
- The game ends when neither player can make a valid move.
- The player with the most discs of their color on the board at the end of the game wins.

Enjoy playing Reversi!
