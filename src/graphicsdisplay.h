#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "display.h"
#include <SFML/Graphics.hpp>

#define SCALE_FACTOR 20

class GraphicsDisplay : public Display {
    public:
        GraphicsDisplay();
        void view() override;
        bool notify(const Subject& whoFrom) override;
    private:
        sf::RenderWindow window;
        void clearScreen();
        friend class Mcomp;
};

#endif
