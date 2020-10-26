#include "display.h"

Display::Display() {
    for(int i = 0; i < HEIGHT; ++i) {
        std::vector<unsigned char> row;
        row.reserve(WIDTH);
        for(int j = 0; j < WIDTH; ++j) {
            row.emplace_back(0);
        }
        screen.emplace_back(row);
    }
}

/*
 * DRW Vx, Vy, nibble
 * Display n-byte sprite at (Vx, Vy), set VF = collision
 */
bool Display::draw(const Info& info, int height, int width) {
    bool collision = false;
    int n = info.sprite.size();
    for(int i = info.Vy; i < info.Vy + n; ++i) {
        uint8_t row = info.sprite.at(i - info.Vy);
        int ctr = 7;
        for(int j = info.Vx; j < info.Vx + REG_SIZE; ++j) {
            if((row >> ctr--) & 0x01) {
                int maxHeight = height - 1, maxWidth = width - 1;
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
    return collision;
}
