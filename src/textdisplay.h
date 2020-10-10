#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "display.h"

#define HEIGHT 64
#define WIDTH 32

class TextDisplay : public Display {
    public:
        TextDisplay();
        void notify(const Subject&) override;
        void view(const DisplayInstruction&) override;
    private:
        std::vector<std::vector<char>> screen;
};

#endif
