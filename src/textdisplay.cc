#include "textdisplay.h"
#include <iostream>

TextDisplay::TextDisplay() {
    for(int i = 0; i < HEIGHT; ++i) {
        std::vector<char> row;
        row.reserve(WIDTH);
        for(int j = 0; j < WIDTH; ++j) {
            row.emplace_back(' ');
        }
        screen.emplace_back(row);
    }
}

void TextDisplay::notify(const Subject& whoFrom) {
    auto info = whoFrom.getInfo();
    if(info.sprite.empty()) {
        /*
         * CLS
         * Clear the display
         */
        clearScreen();
    } else {
        /*
         * DRW Vx, Vy, nibble
         * Display n-byte sprite at (Vx, Vy), set VF = collision
         */


    }
}

void TextDisplay::clearScreen() {
    for(auto &row : screen) {
        for(auto &pixel : row) {
            pixel = ' ';
        }
    }
}

void TextDisplay::view() {
    for(auto const &row : screen) {
        for(auto const &pixel : row) {

        }
    }
}
