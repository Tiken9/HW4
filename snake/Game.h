#pragma once

#include <utility>
#include <list>
#include <functional>

enum Dir
{
    UP, DOWN, LEFT, RIGHT, BODY, RABBIT
};

struct Coord : public std::pair<int, int>
{
    using Base = std::pair<int, int>;
    int distance(const Coord&) const;
    bool is_free;
    using Base :: Base;
};

Coord rand_coord();

class Snake
{
public:
    Snake();
    Snake(const Snake&);

    void set_dir(Dir d);
    void move();
    Coord next_position();

    std::list<Coord> body;
    Dir dir;
    int addit;
    bool is_live;
};

using Rabbit = Coord;

using SnakePainter = std::function<void(Coord, Dir, int)>;


class Game
{
    std::list<Snake*> snakes;


public:
    Game();
    void paint(SnakePainter);
    void move();
    void add(Snake*);
    void add_rabbit();
    std::list<Rabbit> rabbits;
};

