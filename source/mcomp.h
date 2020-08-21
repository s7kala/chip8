#ifndef MCOMP_H
#define MCOMP_H
// microcomputer to run chip8 programs

#include "processor.h"
#include "memory.h"
#include "display.h"

class Mcomp {
    public:
        Mcomp(): CPU{}, RAM{4} {}
    private:
        Processor CPU;
        Memory RAM;
        Display screen;     

};

#endif