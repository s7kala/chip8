#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

/*
 * THIS MODULE IS NOW DEPRECATED AND KEPT ONLY FOR DEBUGGING PURPOSES
 */

#include "display.h"

class TextDisplay : public Display {
    public:
        explicit TextDisplay(std::ostream& out = std::cout);
        bool notify(const Subject&) override;
        void view() override;
    private:
        std::ostream& os;
        void clearScreen();
};

#endif
