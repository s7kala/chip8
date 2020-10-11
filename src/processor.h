#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memory.h"
#include "subject.h"
#include "display.h"
#include <vector>
#include <stack>
#include <cstdint>
#include <random>

#define GPR_NO 16
/*
 * Add later (for now, call stack is environment-dependent)
#define STACK_SIZE 16
*/

class Processor : public Subject {
    public:
        explicit Processor(Memory* pMem);
        /*
         * Init proc (push retAddr to callStack)
         */
        void init(uint16_t retAddr);
        /*
         * Set PC to addr
         */
        void jump(uint16_t addr);
        /*
         * Fetch and execute opcodes
         * Returns true for a successful run of the emulation cycle,
         * false otherwise
         */
        bool run();
        Info getInfo() const override;
    private:
        std::vector<uint8_t> registers;
        uint8_t delay;
        uint8_t sound;
        uint16_t I;
        uint16_t PC;
        uint8_t SP;
        std::stack<uint8_t> callStack;
        Memory* pMem;
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<uint8_t> dist;
        Info displayInstruction;
        void executeInstruction(uint16_t opcode);
        bool compareVxkk(uint16_t opcode);
        bool compareVxVy(uint16_t opcode);
        template<typename T>
        void setVxVy(int Vx, int Vy, T op);
};

#endif
