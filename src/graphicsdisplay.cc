#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(): window{sf::VideoMode(GFX_WIDTH, GFX_HEIGHT), "CHIP-8 Emulator"} {}

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
            sf::RectangleShape rectangle(sf::Vector2f(10, 10));
            rectangle.setPosition(j, i);
            if(!pixel) rectangle.setFillColor(sf::Color(0, 0, 0));
            window.draw(rectangle);
            j += 10;
        }
        i += 10;
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
        /*
         * DRW Vx, Vy, nibble
         * Display n-byte sprite at (Vx, Vy), set VF = collision
         */
        int n = info.sprite.size();
        for(int i = info.Vy; i < info.Vy + n; ++i) {
            uint8_t row = info.sprite.at(i - info.Vy);
            int ctr = 7;
            for(int j = info.Vx; j < info.Vx + REG_SIZE; ++j) {
                if((row >> ctr--) & 0x01) {
                    int maxHeight = HEIGHT - 1, maxWidth = WIDTH - 1;
                    int x = j & maxWidth, y = i & maxHeight;
                    if(screen.at(y).at(x) == 1) {
                        screen.at(y).at(x) = 0;
                        collision = true;
                    } else {
                        screen.at(y).at(x) ^= 1;
                    }
                }
            }
        }
    }
    view();
    return collision;
}