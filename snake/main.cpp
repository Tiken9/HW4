#include "View.h"
#include "Tui.h"
#include "Game.h"
#include "Control.h"


int main() {
    View* v = View::get();

    auto s = new Snake();
    auto g = new Game();
    auto h = new Control_Human(s, g);
    g->add(s);

    std::list<Snake*> ai_snakes;
    for(int i = 0; i < 2; i++)
    {
        ai_snakes.push_back(new Snake());
        g->add(ai_snakes.back());
        new AI(ai_snakes.back(), g);
    }


    v->draw();
    v->run();

    delete v;

    return 0;
}