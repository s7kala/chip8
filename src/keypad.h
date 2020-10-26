#ifndef KEYPAD_H
#define KEYPAD_H

#include <SFML/Graphics.hpp>

/*
 * Keypad                   Keyboard
 * +-+-+-+-+                +-+-+-+-+
 * |1|2|3|C|                |1|2|3|4|
 * +-+-+-+-+                +-+-+-+-+
 * |4|5|6|D|                |Q|W|E|R|
 * +-+-+-+-+       =>       +-+-+-+-+
 * |7|8|9|E|                |A|S|D|F|
 * +-+-+-+-+                +-+-+-+-+
 * |A|0|B|F|                |Z|X|C|V|
 * +-+-+-+-+                +-+-+-+-+
 */
class Keypad {
    public:
        int waitForKey();
        static bool isKeyPressed(int);
        void attach(sf::RenderWindow*);
        bool isConnected();
    private:
        sf::RenderWindow* win;
        static int padToBoard(int k);
};


#endif