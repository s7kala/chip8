#include "keyboard.h"

void Keyboard::attach(sf::RenderWindow* rw) {
    win = rw;
}

/*
 * Key A-F = 0-5
 * Key 0-9 = 26-35
 */
int Keyboard::waitForKey() {
    sf::Event event;
    int key;
    bool keyPressed = false;
    while(!keyPressed) {
        while(win->pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                win->close();
            } else if(event.type == sf::Event::KeyPressed) {
                keyPressed = true;
                int keycode = event.key.code;
                if(keycode >= 0 && keycode <= 5) {
                    key = 10 + keycode;
                } else if(keycode >= 26 && keycode <= 35) {
                    key = keycode - 26;
                } else keyPressed = false;
            }
        }
    }
    return key;
}

bool Keyboard::isKeyPressed(int k) {
    sf::Event event;
    int key = -1;
    while(win->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            win->close();
        } else if(event.type == sf::Event::KeyPressed) {
            int keycode = event.key.code;
            if(keycode >= 0 && keycode <= 5) {
                key = 10 + keycode;
            } else if(keycode >= 26 && keycode <= 35) {
                key = keycode - 26;
            }
        }
    }
    return k == key;
}