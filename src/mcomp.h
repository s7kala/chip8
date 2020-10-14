#ifndef MCOMP_H
#define MCOMP_H

// microcomputer VM to run chip8 programs

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
        explicit Mcomp(bool graphics=false);
        /*
         * Load and then jump to that addr
         */
        void run(const std::string& path, uint16_t addr = BASE_ADDR);
        /*
         * Emulate one instruction
         */
        bool emulate(const std::string& path, uint16_t addr = BASE_ADDR);
        /*
         * Boot up a program
         */
        void boot(const std::string& path, uint16_t addr = BASE_ADDR);
        ~Mcomp();
    private:
        Memory* RAM;
        Processor CPU;
        Display* screen;
        bool graphics;
        /*
         * Load a program with filepath "path" into memory at
         * starting address "addr", returns end addr
         */
        uint16_t load(const std::string& path, uint16_t addr = BASE_ADDR);
};

#endif
