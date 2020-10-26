#ifndef DISPLAY_H
#define DISPLAY_H

#include "observer.h"
#include "subject.h"
#include <iostream>

#define REG_SIZE 8
#define HEIGHT 32
#define WIDTH 64

class Display : public Observer {
    public:
        Display();
        virtual void view() = 0;
        ~Display() override = default;
    protected:
        std::vector<std::vector<unsigned char>> screen;
        bool draw(const Info&, int height = HEIGHT, int width = WIDTH);
};

#endif
