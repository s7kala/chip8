#ifndef DISPLAY_H
#define DISPLAY_H

#include "observer.h"
#include <iostream>

#define REG_SIZE 8


class Display : public Observer {
    public:
        virtual void view() = 0;
        ~Display() override = default;
};

#endif
