#pragma once

#include <termios.h>
#include "View.h"


class Tui : public View
{
    int x,y;
    struct termios old_opt;


public:

    Tui();
    ~Tui() override;

    void draw() override;
    void run() override;

    void snakepainter(Coord a, Dir t, int color) override;

    void set_color(int);

    Coord window_size() override;

    void get_win_size();
    void gotoxy(int x, int y);
    void print_frame();
    void clear_screen();
};



