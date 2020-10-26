#include "textdisplay.h"

TextDisplay::TextDisplay(std::ostream& os): os{os} {}

bool TextDisplay::notify(const Subject& whoFrom) {
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

void TextDisplay::clearScreen() {
    for(auto &row : screen) {
        for(auto &pixel : row) {
            pixel = 0;
        }
    }
}

void TextDisplay::view() {
   // os << "\033[2J\033[1;1H";
    for(auto const &row : screen) {
        for(auto const &pixel : row) {
            if(pixel)
                os << '*';
            else os << ' ';
        }
        os << '\n';
    }
}
