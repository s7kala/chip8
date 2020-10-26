#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Graphics.hpp>

class Keyboard {
    public:
        int waitForKey();
        bool isKeyPressed(int);
        void attach(sf::RenderWindow*);
    private:
        sf::RenderWindow* win;
};


#endif