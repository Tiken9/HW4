#include <iostream>
#include <algorithm>
#include <random>
#include "Control.h"
#include "View.h"


Control::Control(Snake *s, Game *g)
{
    model = s;
    game = g;
}

Control_Human::Control_Human(Snake* s, Game* g) : Control(s, g)
{
    View* v = View::get();
    v->set_onkey(this);

}

void Control_Human::onkey(int key)
{
    if(!model->is_live)
        return;
    switch (key) {
        case 'w':
            model->set_dir(UP);
            break;
        case 'a':
            model->set_dir(LEFT);
            break;
        case 'd':
            model->set_dir(RIGHT);
            break;
        case 's':
            model->set_dir(DOWN);
            break;
        default:
            break;
    }

    View* v = View::get();
    v->draw();
}

AI::AI(Snake *s, Game *g) : Control(s, g)
{
    View* v = View::get();
    v->set_on_move(this);
}

void AI::on_move()
{
    View* v = View::get();
    Coord win_size = v->window_size();
    if(!model->is_live)
        return;
    Dir dir[] = {UP, DOWN, RIGHT, LEFT} ;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> uid(1, 5);
    std::shuffle(dir, dir + 3, g);

    auto head = model->body.front();
    int a, min_distance = 1000;
    Coord aim;
    for(auto r : game->rabbits)
    {
        if((a = head.distance(r)) < min_distance)
        {
            min_distance = a;
            aim = r;
        }
    }


    for(auto d : dir)
    {
        Dir old  = model->dir;
        bool rightly = true;
        model->dir = d;
        for(auto elem : model->body)
        {
            if(elem == model->next_position())
            {
                model->dir = old;
                rightly = false;
                break;
            }
            if(model->next_position().second == 1 || model->next_position().second == win_size.second
               || model->next_position().first == 1 || model->next_position().first == win_size.first)
            {
                model->dir = old;
                rightly = false;
                break;
            }
        }
        if(model->next_position().distance(aim) < min_distance && rightly)
            break;
    }
}

