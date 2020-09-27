#include "processor.h"

Processor::Processor(Memory* pMem): pMem{pMem} {
    for(int i = 0; i < GPR_NO; ++i)
        registers.emplace_back(0);
    delay = sound = I = PC = SP = 0;
}

void Processor::jump(uint16_t addr) {
    PC = addr;
}

void Processor::run(uint16_t retAddr) {
    stack.emplace_back(retAddr);
    SP = stack.front();
    while(!stack.empty()) {
        uint16_t opcode = (pMem->getAddr(PC) << 8) + pMem->getAddr(PC + 1);
        PC += 2;
        executeInstruction(opcode);
    }
}

Info Processor::getInfo() const {

}

void Processor::executeInstruction(uint16_t opcode) {
    switch (opcode) {
        // Clear display
        case 0x00e0:
            break;
        // Return from a subroutine
        case 0x00EE:
            break;
        
    }
}
