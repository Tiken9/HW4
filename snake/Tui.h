#pragma once

#include <termios.h>
#include "View.h"


class Tui : public View
{
    int x,y;
    struct termios old_opt;


public:

    Tui();
    ~Tui();

    void draw() override;
    void run() override;

    void snakepainter(Coord a, Dir t) override ;

    void get_win_size();
    void gotoxy(int x, int y);
    void print_frame();
    void clear_screen();
};



