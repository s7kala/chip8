#include "processor.h"
#include "ch8excepts.h"

/*
 * TO-DO:
 * Can possibly replace member SP with typedef callStack.top()
 */

Processor::Processor(Memory* pMem): pMem{pMem} {
    for(int i = 0; i < GPR_NO; ++i)
        registers.emplace_back(0);
    delay = sound = I = PC = SP = 0;
}

void Processor::jump(uint16_t addr) {
    PC = addr;
}

void Processor::run(uint16_t retAddr) {
    callStack.push(retAddr);
    SP = callStack.top();
    while(!callStack.empty()) {
        uint16_t opcode = (pMem->getAddr(PC) << 8) + pMem->getAddr(PC + 1);
        PC += 2;
        executeInstruction(opcode);
    }
}

Info Processor::getInfo() const {

}

/* REMOVE THIS SOON - WRITE A MORE GENERAL HELPER TO RETURN Vxkk and VxVy
 * Returns true if register Vx == kk
 */
bool Processor::compareVxkk(uint16_t opcode) {
    auto regNo = (opcode & 0x0f00) >> 8;
    uint8_t byte = (opcode & 0x00ff);
    return (registers.at(regNo) == byte);
}

void Processor::executeInstruction(uint16_t opcode) {
    switch (opcode) {
        /*
         * 00E0 - CLS
         * Clear the display
         */
        case 0x00e0:
            break;
        /*
         * 00EE - RET
         * Return from a subroutine
         */
        case 0x00ee:
            PC = callStack.top();
            callStack.pop();
            if(callStack.empty())
                // potential hazard for subsequent run calls/SMP scaling
                SP = 0;
            else SP = callStack.top();
            break;
        /*
         * 1nnn - JP addr
         * Jump to location nnn
         */
        case 0x1000 ... 0x1fff:
            PC = opcode - 0x1000;
            break;
        /*
         * 2nnn - CALL addr
         * Call subroutine at nnn
         */
        case 0x2000 ... 0x2fff:
            callStack.push(PC);
            SP = callStack.top();
            PC = opcode - 0x2000;
            break;
        /*
         * 3xkk - SE Vx, byte
         * Skip next instruction if Vx = kk
         */
        case 0x3000 ... 0x3fff:
            if(compareVxkk(opcode))
                PC += 2;
            break;
        /*
         * 4xkk - SNE Vx, byte
         * Skip next instruction if Vx != kk
         */
        case 0x4000 ... 0x4fff:
            if(!compareVxkk(opcode))
                PC += 2;
            break;
        /*
         * 5xy0 - SE Vx, Vy
         * Skip next instruction if Vx = Vy
         */
        default: throw InvalidCPUInstruction("Unrecognized CPU instruction : " + std::to_string(opcode));
    }
}
