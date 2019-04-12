#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

#include "Tui.h"
#include "Game.h"


void win_sz_handler(int sign_n)
{
    View* a = View::get();
    a->draw();
}

Tui::Tui()
{
    get_win_size();

    struct sigaction win = {};

    win.sa_handler = &win_sz_handler;
    win.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &win, NULL);

    struct termios opt;
    tcgetattr(0, &opt);
    old_opt = opt;
    cfmakeraw(&opt);
    tcsetattr(0, TCSAFLUSH, &opt);

    View::inst = this;
}


void Tui::get_win_size()
{
    struct winsize Window;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &Window);

    this->x = Window.ws_col;
    this->y = Window.ws_row;
}


void Tui::print_frame()
{
    for(int i = 0; i < y + 1; i++)
    {
        if(i == 0 || i == (y))
        {
            printf("\033[%d;%dH#", i, 1);
            for (int k = 0; k < x - 1; k++)
                fputs("#", stdout);
            fflush(stdout);
        }
        else
        {
            printf("\033[%d;%dH#\n", i, 1);
            printf("\033[%d;%dH#\n", i, x);
        }
    }
}


void Tui::clear_screen()
{
    printf("\033[2J");
    printf("\033[0;0f");
}


void Tui::snakepainter(Coord a, Dir t)
{
    gotoxy(a.first, a.second);
    putchar("^v<>o"[t]);
}


void Tui::draw()
{
    get_win_size();

    clear_screen();
    print_frame();

    SnakePainter f = std::bind(&View::snakepainter, this, std::placeholders::_1, std::placeholders::_2);
    game->paint(f);


}


void Tui::gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}


void Tui::run()
{
    int key = -1;
    while ((key = getchar()))
    {
        if(key == 'x' || key == -1)
            break;

        onkey_delegate->onkey(key);
    }

}


Tui::~Tui()
{
    clear_screen();
    tcsetattr(0, TCSAFLUSH, &old_opt);
}

