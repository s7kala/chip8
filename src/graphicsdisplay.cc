#include "graphicsdisplay.h"

void renderingThread(sf::RenderWindow* window) {
    window->setActive(true);
    sf::Image img;
   // img.create(GFX_WIDTH, GFX_HEIGHT, screen.data());
   // while(window->isOpen()) {

   //     window->display();
   // }
}

GraphicsDisplay::GraphicsDisplay(): window{sf::VideoMode(GFX_WIDTH, GFX_HEIGHT), "SFML Window"} {
    window.setActive(false);
    sf::Thread thread(&renderingThread, &window);
    thread.launch();
    for(int i = 0; i < GFX_HEIGHT * GFX_WIDTH; ++i) {
        screen.emplace_back(0);
    }
}

void GraphicsDisplay::clearScreen() {
    window.clear(sf::Color(0));
}

void GraphicsDisplay::view() {

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

        int n = info.sprite.size();
        for(int i = info.Vy; i < info.Vy + n; ++i) {
            uint8_t row = info.sprite.at(i - info.Vy);
            int ctr = 7;
            for(int j = info.Vx; j < info.Vx + REG_SIZE; ++j) {
                if((row >> ctr--) & 0x01) {
                    int maxHeight = GFX_HEIGHT - 1, maxWidth = GFX_WIDTH - 1;
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
         */
    }
    view();
    return collision;
}