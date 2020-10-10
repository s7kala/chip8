#include "textdisplay.h"

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

}

void TextDisplay::view(const DisplayInstruction& instr) {

}
