#ifndef MCOMP_H
#define MCOMP_H

// microcomputer to run chip8 programs

#include "processor.h"
#include "memory.h"
#include "display.h"

#include <string>

class Mcomp {
    public:
        Mcomp();
        /*
         * Load a program with filepath "path" into memory at
         * starting address "addr"
         */
        void load(const std::string& path, unsigned int addr);
        /*
         * Load and then jump to that addr
         */
        void run(const std::string& path, unsigned int addr);
    private:
        Processor CPU;
        Memory RAM;
        Display screen;
};

#endif