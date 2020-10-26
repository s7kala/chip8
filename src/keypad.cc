#include "keypad.h"
#include <SFML/Graphics.hpp>

void Keypad::attach(sf::RenderWindow* rw) {
    win = rw;
}

int Keypad::padToBoard(int k) {
    int key;
    switch(k) {
        case 0: key = sf::Keyboard::X; break;
        case 1: key = sf::Keyboard::Num1; break;
        case 2: key = sf::Keyboard::Num2; break;
        case 3: key = sf::Keyboard::Num3; break;
        case 4: key = sf::Keyboard::Q; break;
        case 5: key = sf::Keyboard::W; break;
        case 6: key = sf::Keyboard::E; break;
        case 7: key = sf::Keyboard::A; break;
        case 8: key = sf::Keyboard::S; break;
        case 9: key = sf::Keyboard::D; break;
        case 10: key = sf::Keyboard::Z; break;
        case 11: key = sf::Keyboard::C; break;
        case 12: key = sf::Keyboard::Num4; break;
        case 13: key = sf::Keyboard::R; break;
        case 14: key = sf::Keyboard::F; break;
        case 15: key = sf::Keyboard::V; break;
        default: key = -1;
    }
    return key;
}

/*
 * Key A-F = 0-5
 * Key 0-9 = 26-35
 */
int Keypad::waitForKey() {
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

bool Keypad::isKeyPressed(int k) {
    int key = padToBoard(k);
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
}

bool Keypad::isConnected() {
    return (win != nullptr);
}
