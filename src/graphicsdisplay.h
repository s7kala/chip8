#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "display.h"
#include <SFML/Graphics.hpp>

#define GFX_WIDTH 640
#define GFX_HEIGHT 320

class GraphicsDisplay : public Display {
    public:
        GraphicsDisplay();
        void view() override;
        bool notify(const Subject& whoFrom) override;
    private:
        sf::RenderWindow window;
        std::vector<sf::Uint8> screen;
        void clearScreen();
        friend class Mcomp;
};

#endif
