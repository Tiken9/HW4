#include <iostream>
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
    switch(key)
    {
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
    game->move();

    View* v = View::get();
    v->draw();
}