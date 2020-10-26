#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

/*
 * THIS MODULE IS NOW DEPRECATED AND KEPT ONLY FOR DEBUGGING PURPOSES
 */

#include "display.h"

#define HEIGHT 32
#define WIDTH 64

class TextDisplay : public Display {
    public:
        explicit TextDisplay(std::ostream& out = std::cout);
        bool notify(const Subject&) override;
        void view() override;
    private:
        std::vector<std::vector<unsigned char>> screen;
        std::ostream& os;
        void clearScreen();
};

#endif
