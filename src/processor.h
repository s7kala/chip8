#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "register.h"
#include <vector>

#define GPR_NO 16

class Processor {
    public:
        Processor();
        void jump(unsigned int addr);
    private:
        std::vector<Register> registers;
        Register delay;
        Register sound;
        Register I[2];
        Register PC[2];
};

#endif