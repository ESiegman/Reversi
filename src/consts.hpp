#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <cstdint>
#include <array>

constexpr uint8_t BOARD_LENGTH = 8;
constexpr std::array<std::array<int, 2>, 8> DIRECTIONS = {{
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
}};
constexpr uint8_t MAX_DEPTH = 10;
constexpr uint8_t CORNER_WEIGHT = 10;
constexpr uint8_t SIDE_WEIGHT = 5;

#endif
