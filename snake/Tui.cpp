#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/poll.h>

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
    sigaction(SIGWINCH, &win, nullptr);

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
    set_color(0);
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


void Tui::snakepainter(Coord a, Dir t, int color)
{
    gotoxy(a.first, a.second);
    set_color(color);
    putchar("^v<>o@"[t]);


}

void Tui::set_color(int c)
{
    printf("\033[%dm", c);
}



void Tui::draw()
{
    get_win_size();

    clear_screen();
    print_frame();

    SnakePainter f = std::bind(&View::snakepainter, this, std::placeholders::_1, std::placeholders::_2,
            std::placeholders::_3);

    game->paint(f);
    gotoxy(1,1);
    fflush(stdout);
}


void Tui::gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}


void Tui::run()
{
    int n;
    char key;
    while(1)
    {
        struct pollfd our = {};
        our.fd = STDIN_FILENO;
        our.events = POLLIN;
        n = poll(&our, 1, timer.first);
        if(n == 1)
        {
            read(STDIN_FILENO, &key, 1);
            if(key == 'x' || key == -1)
                break;

            onkey_delegate->onkey(key);
        }
        else if(n == 0)
        {
            for(auto ai : on_move_delegate)
                ai->on_move();
            timer.second();
            draw();
        }
        else
        {

        }
    }
}


Tui::~Tui()
{
    clear_screen();
    tcsetattr(0, TCSAFLUSH, &old_opt);
}

Coord Tui::window_size()
{
    Coord win;
    win.first = x;
    win.second = y;
    return win;
}