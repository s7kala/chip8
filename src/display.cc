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
