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

    v->draw();
    v->run();

    delete v;

    return 0;
}