#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memory.h"
#include "subject.h"
#include <vector>
#include <cstdint>

#define GPR_NO 16
#define STACK_SIZE 16

class Processor : public Subject {
    public:
        explicit Processor(Memory* pMem);
        /*
         * Set PC to addr
         */
        void jump(uint16_t addr);
        /*
         * Fetch and execute opcodes
         */
        void run(uint16_t retAddr);
        Info getInfo() const override;
    private:
        std::vector<uint8_t> registers;
        uint8_t delay;
        uint8_t sound;
        uint16_t I;
        uint16_t PC;
        uint8_t SP;
        std::vector<uint8_t> stack;
        Memory* pMem;
        void executeInstruction(uint16_t opcode);
};

#endif