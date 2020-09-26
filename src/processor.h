#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "register.h"

class Processor {
    public:
        void jump(unsigned int addr);
    private:
        Register registers[16];
        unsigned int PC;
};

#endif