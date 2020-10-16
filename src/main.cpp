
#include <iostream>
#include "screen.h"


const int WIDTH  = 800;
const int HEIGHT = 800;


int main(){

    Screen *screen = new Screen(WIDTH , HEIGHT);

    // The user might quit the game on the ship menu, in this case, do not render
    if(screen->menu())
        screen->render();

    return 0;
}