#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
using namespace sf;



int main() {
    RenderWindow window(VideoMode(1200, 800), "Menu");
    //window.setFramerateLimit(60);

    Menu m(window.getSize().x, window.getSize().y);
    m.display_menu(window);
    return 0;
}
