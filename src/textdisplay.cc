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
        collision = Display::draw(info);
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
