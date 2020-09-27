#ifndef MCOMP_H
#define MCOMP_H

// microcomputer to run chip8 programs

#include "processor.h"

#include <string>

#ifdef ETI660
#define BASE_ADDR 0x600
#else
#define BASE_ADDR 0x200
#endif

class Memory;
class Display;
class Mcomp {
    public:
        Mcomp();
        /*
         * Load and then jump to that addr
         */
        void run(const std::string& path, uint16_t addr = BASE_ADDR);
        ~Mcomp();
    private:
        Processor CPU;
        Memory *RAM;
        Display *screen;
        /*
         * Load a program with filepath "path" into memory at
         * starting address "addr", returns end addr
         */
        uint16_t load(const std::string& path, uint16_t addr = BASE_ADDR);
};

#endif