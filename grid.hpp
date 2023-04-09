#ifndef _GRID_HPP
#define _GRID_HPP

#include <map>
#include <set>

class Grid
{
    private:
        std::set<std::pair<int, int>> cells;
        std::set<std::pair<int, int>> get_neighbors(std::pair<int, int> cell);
        std::multiset<std::pair<int, int>> count_live_neighbors();
        std::map<std::pair<int, int>, int> reducer(std::multiset<std::pair<int, int>> neighbor_counter);

    public:
        Grid();
        Grid(std::set<std::pair<int, int>> _cells);

        const std::set<std::pair<int, int>>& get_cells();
        void toggle_cell(std::pair<int, int> cell);
        // Computes the state each cell will have next frame

        void compute();
        void compute(int iterations);
};

#endif
