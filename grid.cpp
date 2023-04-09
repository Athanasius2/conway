#include <map>
#include <set>
#include <stdexcept>

#include "grid.hpp"

// Return the set of 8 adjacent coordinates to cell
std::set<std::pair<int, int>> Grid::get_neighbors(std::pair<int, int> cell)
{
    return std::set<std::pair<int, int>> {
        std::pair<int, int>(cell.first - 1  , cell.second - 1   ),
        std::pair<int, int>(cell.first - 1  , cell.second       ),
        std::pair<int, int>(cell.first - 1  , cell.second + 1   ),
        
        std::pair<int, int>(cell.first      , cell.second - 1   ),
        std::pair<int, int>(cell.first      , cell.second + 1   ),
        
        std::pair<int, int>(cell.first + 1  , cell.second - 1   ),
        std::pair<int, int>(cell.first + 1  , cell.second       ),
        std::pair<int, int>(cell.first + 1  , cell.second + 1   )
    };
}

// return a multiset of pairs (x, y) where each instance of (x, y) represents a neighbor of (x, y)
std::multiset<std::pair<int, int>> Grid::count_live_neighbors()
{
    std::multiset<std::pair<int, int>> neighbor_counter;
    for (auto cell : cells)
    {// O(n)
        auto neighbors = get_neighbors(cell);
        neighbor_counter.insert(neighbors.begin(), neighbors.end()); // O(lg n)
    } // Total complexity O(n lg n)
    return neighbor_counter;
}

// Take multiset created by count_live_neighbors and create a map where they key is the coordinates
// and the value is the number of neighbors for that
std::map<std::pair<int, int>, int> Grid::reducer(std::multiset<std::pair<int, int>> neighbor_counter)
{
    std::map<std::pair<int, int>, int> reduced;

    for (auto cell : neighbor_counter)
    {
        std::pair<const std::pair<int, int>, int> ins(cell, 1);

        auto pair_of_iterator_bool = reduced.insert(ins);   //pair<iter, bool>
        // iter_pair.second will be false if the key already existed
        if (!pair_of_iterator_bool.second)
            reduced[cell]++; // Key already exists, so increment value
    }

    return reduced;
}

void Grid::compute()
{
    auto neighbor_counter = count_live_neighbors();
    auto reduced = reducer(neighbor_counter);
 
    // update grid
    auto cellsIterator = cells.begin();
    
    while (cellsIterator != cells.end())
    { // O(n)
        // Some cells have no neighbors so they will not appear in 'reduced'
        // If this happens, erase the cell from cells
        try
        {
            if (reduced[*cellsIterator] < 2 || reduced[*cellsIterator] > 3)
                cellsIterator = cells.erase(cellsIterator);
            else
                cellsIterator++;
        
        }
        catch(const std::out_of_range& e)
        {
            cellsIterator = cells.erase(cellsIterator);
        }
    }

    // Check cells remaining in reduced to see if new cells are born
    for (auto cell : reduced)
    { // O(n)
        if (cell.second == 3)
            cells.insert(cell.first);
    }
}

void Grid::compute(int iterations)
{
    for (int i = 0; i < iterations; i++)
        compute();
}

void Grid::toggle_cell(std::pair<int, int> cell)
{
    auto pair_of_iterator_bool = cells.insert(cell);
    if (!pair_of_iterator_bool.second)
        cells.erase(pair_of_iterator_bool.first);
}

const std::set<std::pair<int, int>>& Grid::get_cells()
{
    return cells;
}

Grid::Grid(std::set<std::pair<int, int>> _cells)
{
    cells = _cells;
}