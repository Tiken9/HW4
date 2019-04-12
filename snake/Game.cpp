#include "Game.h"
#include "View.h"

void Game::paint(SnakePainter p)
{
    bool st = true;

    for(auto s: snakes)
        for(const auto& c: s->body)
        {
            p(c, st ? s->dir : BODY);
            st = false;
        }
}

Game::Game()
{
    View* v = View::get();
    v->set_model(this);
}

void Game::move()
{
    for(auto s : snakes)
        s->move();
}

void Game::add(Snake* s)
{
    snakes.push_back(s);
}

Snake::Snake()
{
    body.push_back(Coord(11,15));
    body.push_back(Coord(12,15));
    body.push_back(Coord(13,15));
    dir = LEFT;
}

Snake::Snake(const Snake& s) :
    body(s.body), dir(s.dir)
{}

void Snake::move()
{
    auto head = body.front();
    switch(this->dir)
    {
        case UP:
            head.second--;
            break;
        case LEFT:
            head.first--;
            break;
        case DOWN:
            head.second++;
            break;
        case RIGHT:
            head.first++;
            break;
        default:
            break;
    }
    body.push_front(head);
    body.pop_back();
}

void Snake::set_dir(Dir d)
{
    dir = d;
}