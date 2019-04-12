#pragma once

#include <utility>
#include <list>
#include <functional>
enum Dir
{
    UP, DOWN, LEFT, RIGHT, BODY
};

using Coord = std::pair<int, int>;


class Snake
{
public:
    Snake();
    Snake(const Snake&);

    void set_dir(Dir d);
    void move();

    std::list<Coord> body;
    Dir dir;
};

using Rabbit = Coord;

using SnakePainter = std::function<void(Coord, Dir)>;


class Game
{
    std::list<Snake*> snakes;
    std::list<Rabbit> rabbits;

public:
    Game();
    void paint(SnakePainter );
    void move();
    void add(Snake*);
};

