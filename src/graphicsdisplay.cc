#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay():
    window{sf::VideoMode(WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR), "CHIP-8 Emulator"} {}
void GraphicsDisplay::clearScreen() {
    for(auto &row : screen) {
        for(auto &pixel : row) {
            pixel = 0;
        }
    }
    view();
}

void GraphicsDisplay::view() {
    int i = 0;
    for(auto const &row : screen) {
        int j = 0;
        for(auto const &pixel : row) {
            sf::RectangleShape rectangle(sf::Vector2f(SCALE_FACTOR, SCALE_FACTOR));
            rectangle.setPosition(j, i);
            if(!pixel) rectangle.setFillColor(sf::Color(0, 0, 0));
            window.draw(rectangle);
            j += SCALE_FACTOR;
        }
        i += SCALE_FACTOR;
    }
    window.display();
}

bool GraphicsDisplay::notify(const Subject &whoFrom) {
    auto info = whoFrom.getInfo();
    bool collision = false;
    if(info.sprite.empty()) {
        /*
         * CLS
         * Clear the display
         */
        clearScreen();
    } else {
        collision = Display::draw(info);
    }
    view();
    return collision;
}