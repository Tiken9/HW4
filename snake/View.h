#pragma once

#include "Game.h"
#include "Keypressable.h"
#include "Control.h"

#include <utility>
#include <list>
#include <functional>

using timer_fn = std::function<void(void)>;

class View
{
public:

    virtual void draw() = 0;
    virtual void run() = 0;
    virtual void snakepainter(Coord c, Dir d, int color) = 0;
    virtual ~View();

    virtual Coord window_size() = 0;

    static View* get();
    static View* inst;

    void set_model(Game *g);
    void set_onkey(Keypressable *k);
    void set_on_move(AI *a);
    void set_ontimer(int, timer_fn);
    std::pair<int, timer_fn> timer;

    Game* game;
    Keypressable* onkey_delegate;
    std::list <AI*> on_move_delegate;

};

