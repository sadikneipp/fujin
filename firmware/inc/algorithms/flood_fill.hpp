#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

#include "utils/RingBuffer.hpp"

enum Walls {
    N = 1 << Direction::NORTH,
    E = 1 << Direction::EAST,
    S = 1 << Direction::SOUTH,
    W = 1 << Direction::WEST,
};

namespace algorithm {

struct Cell {
    uint8_t value;
    uint8_t walls;
    bool visited;

    Cell* north;
    Cell* east;
    Cell* south;
    Cell* west;

    void update_walls(uint8_t walls) {
        this->walls = walls;

        if (walls & N && north != nullptr) {
            north->walls |= S;
        }

        if (walls & E && east != nullptr) {
            east->walls |= W;
        }

        if (walls & S && south != nullptr) {
            south->walls |= N;
        }

        if (walls & W && west != nullptr) {
            west->walls |= E;
        }
    }
};

template <int width, int height>
using Grid = Cell[width][height];

template <int width, int height>
void flood_fill(Grid<width, height>& grid, Point const& target) {
    // Reset the value of every cell
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            grid[x][y].value = 255;
        }
    }
    grid[target.x][target.y].value = 0;

    RingBuffer<Point, 32> to_visit;
    to_visit.put(target);

    static constexpr Point Δ[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!to_visit.empty()) {
        Point pos;
        to_visit.get(&pos);
        Cell& cell = grid[pos.x][pos.y];

        // Iterate every direction
        for (auto& d : Directions) {
            Point next = pos + Δ[d];

            // out of bounds
            if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height) {
                continue;
            }

            Cell& next_cell = grid[next.x][next.y];

            bool has_wall = (cell.walls & (1 << d)) != 0;
            bool visited = next_cell.value != 255;

            // We can't or don't need to visit this cell
            if (has_wall || visited) {
                continue;
            }

            next_cell.value = cell.value + 1;
            to_visit.put(next);
        }
    }
}

}
