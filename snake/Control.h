#pragma once
#include "Keypressable.h"
#include "Game.h"

class Control
{
public:
    Control(Snake* s, Game* g);

protected:
    Snake* model;
    Game* game;
};

class Control_Human : public Keypressable, public Control
{
public:
    Control_Human(Snake* s, Game* g);
    void onkey(int key) override;
};

