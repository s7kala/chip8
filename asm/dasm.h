/*
 * CHIP-8 Disassembler Header
 * $PROJECT_ROOT/asm/dasm.h
 */

#ifndef DASM_H
#define DASM_H

#include <iostream>
#include <string>

class Disassembler {
    public:
        explicit Disassembler(bool verbose = false);
        static void disassemble(const std::string&, std::ostream&);
        static void decodeInstruction(uint16_t, std::ostream&, int);
    private:
        bool verbose;
};


#endif