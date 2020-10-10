#ifndef DISPLAY_H
#define DISPLAY_H

#include "observer.h"

enum class DisplayInstruction {Clear};

class Display : public Observer {
    public:
        virtual void view(const DisplayInstruction&) = 0;
        ~Display() override = default;
};

#endif
