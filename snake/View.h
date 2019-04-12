#pragma once

#include "Game.h"
#include "Keypressable.h"

#include <utility>
#include <list>
#include <functional>

class View
{
public:

    virtual void draw() = 0;
    virtual void run() = 0;
    virtual void snakepainter(Coord c, Dir d) = 0;
    virtual ~View();

    static View* get();
    static View* inst;

    void set_model(Game *g);
    void set_onkey(Keypressable* k);


    Game* game;
    Keypressable* onkey_delegate;

};

