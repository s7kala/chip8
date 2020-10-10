/*
 * CHIP-8 Assembler Header
 * $PROJECT_ROOT/asm/asm.h
 */

#ifndef ASM_H
#define ASM_H

#include <iostream>
#include <string>

class Assembler {
    public:
        explicit Assembler(bool verbose = false);
        void assemble(const std::string&, std::ostream&);
    private:
        bool verbose;
};

#endif