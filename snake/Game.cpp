#include <random>
#include "Game.h"
#include "View.h"

#define RAB_PROB 5

void Game::paint(SnakePainter p) {
    bool st;
    int iter = 31;

    for (auto s: snakes)
    {
        st = true;
        for (const auto &c: s->body)
        {
            p(c, st ? s->dir : BODY, iter);
            st = false;
        }
        iter++;
    }
    for(auto r: rabbits)
        p(r, RABBIT, 0);
}

Game::Game()
{
    View* v = View::get();
    v->set_model(this);
    v->set_ontimer(500, std::bind(&Game::move, this));


}

void Game::move()
{
    View* v = View::get();
    Coord win_size = v->window_size();

    for(auto s : snakes)
    {
        auto head = s->next_position();
        for(auto r : rabbits)
            if(r == head)
            {
                s->addit++;
                rabbits.remove(r);
                break;
            }

        for(auto other : snakes)
        {
            for(auto obstacle : other->body)
            {
                if(obstacle == head)
                    s->is_live = false;
            }
        }

        if(head.second == 1 || head.second == win_size.second || head.first == 1 || head.first == win_size.first)
        {
            s->is_live = false;
        }

        s->move();
    }
    add_rabbit();
}

void Game::add(Snake* s)
{
    snakes.push_back(s);
}

Snake::Snake()
{

    body.push_back(rand_coord());

    dir = LEFT;
    addit = 2;
    is_live = true;
}

Snake::Snake(const Snake& s) :
    body(s.body), dir(s.dir), addit(s.addit)
{}

void Snake::move()
{
    if(is_live) {
        body.push_front(next_position());

        if (addit == 0) {
            body.pop_back();
            return;
        }

        addit--;
    }
}


void Snake::set_dir(Dir d)
{
    dir = d;
}


int Coord::distance(const Coord& b)  const
{
    return std::abs(b.first - this->first) + std::abs(b.second - this->second);
}

void Game::add_rabbit() {

    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> uid(1, RAB_PROB);

    if(rabbits.size() < 6 && uid(g) == 2)
        rabbits.emplace_back(rand_coord());
}

Coord Snake::next_position()
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

    return head;
}

Coord rand_coord()
{
    View *v = View::get();
    Coord win = v->window_size();

    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> uidX(2, win.first - 2);
    std::uniform_int_distribution<> uidY(2, win.second - 2);
    return Coord(uidX(g), uidY(g));
}