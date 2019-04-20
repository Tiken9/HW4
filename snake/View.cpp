#include <iostream>
#include "View.h"
#include "Tui.h"
#include <sys/ioctl.h>
#include <unistd.h>


View* View::inst = nullptr;

View::~View() {}

View* View::get()
{
    if(inst)
        return inst;

    inst = new Tui;

    return inst;
}
void View::set_model(Game *g)
{
    game = g;
}
void View::set_onkey(Keypressable *k)
{
    onkey_delegate = k;
}

void View::set_on_move(AI *a)
{
    on_move_delegate.push_back(a);
}

void View::set_ontimer(int time, timer_fn func)
{
    timer.first = time;
    timer.second = func;
}

