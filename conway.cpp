
//Conway's Game of Life implemented using MapReduce algorithm.
//Gabriel Kanakares

#include <string>
#include <sstream>
#include <ncurses.h>

#include "grid.hpp"

struct Offset {
        int x{0};
        int y{0};
};

int generation = 0;

void draw_grid(const std::set<std::pair<int, int>>& grid, Offset camera, Offset cursor)
{
    clear();
    std::stringstream ss;
    ss << "X: " << camera.x << ", Y: " << camera.y << ", Population: " << grid.size() << ", Generation: " << generation;
    std::string coords = ss.str();

    // draw new stuff before we refresh

    for (auto c : grid)
    {
        mvaddch(c.first - camera.y, c.second - camera.x, '#');
    }
    //reset cursor position after done drawing
    move(0, 0);
    addstr(coords.c_str());

    move(cursor.y, cursor.x);
    refresh();
}

int main(int argc, char** argv)
{
    //initialize grid with glider
    std::set<std::pair<int, int>> glider{
        std::pair<int, int>(0, 0),
        std::pair<int, int>(0, 1),
        std::pair<int, int>(0, 2),
        std::pair<int, int>(1, 0),
        std::pair<int, int>(2, 1)
    };

    Grid grid(glider);

    //create camera to act as an offest for drawing 
    Offset camera;
    //cursor will always be positioned relative to camera
    Offset cursor;
    bool quit = false;

    // load values into grid

    initscr();
    raw();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (!quit)
    {
        draw_grid(grid.get_cells(), camera, cursor);
        int ch = getch();

        switch (ch)
        {
        case 'q':
            quit = true;
            break;

        case ' ':
            grid.compute();
            generation++;
            break;

        case KEY_UP:
            camera.y--;
            break;

        case KEY_DOWN:
            camera.y++;
            break;

        case KEY_LEFT:
            camera.x--;
            break;
        
        case KEY_RIGHT:
            camera.x++;
            break;
        
        case 'w':
            cursor.y--;
            break;

        case 's':
            cursor.y++;
            break;

        case 'a':
            cursor.x--;
            break;
        
        case 'd':
            cursor.x++;
            break;

        case KEY_ENTER:
        case '\n':
            grid.toggle_cell(std::pair<int, int>(camera.y + cursor.y, camera.x + cursor.x));
            break;

        default:
            break;
        }
    }

    echo();
    noraw();
    endwin();
    return 0;
}