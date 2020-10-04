#include "processor.h"
#include "ch8excepts.h"

/*
 * TO-DO:
 * Can possibly replace member SP with typedef callStack.top()
 */

/* ***************************** METHOD ABSTRACTIONS ********************************* */


/* ********** COMMON FUNCTIONS AND HELPERS ************* */

/*
 * Return index of register Vx from opcode LxMN
 */
int getVx(uint16_t opcode) {
    int vx = (opcode & 0x0f00) >> 8;
    return vx;
}

/*
 * Return index of register Vx and byte kk from opcode nxkk
 */
std::pair<int, uint8_t> getVxkk(uint16_t opcode) {
    uint8_t byte = (opcode & 0x00ff);
    return std::make_pair(getVx(opcode), byte);
}

/*
 * Return index of register Vx and Vy from opcode nxym
 */
std::pair<int, int> getVxVy(uint16_t opcode) {
    return std::make_pair(getVx(opcode), getVx(opcode << 4));
}

/*
 * Throw exception on invalid opcode
 */
void InvalidCPUInstr(uint16_t opcode) {
    throw InvalidCPUInstruction("Unrecognized CPU instruction " + std::to_string(opcode));
}



/* ********************************* METHODS *************************************** */

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

uint8_t addReg(uint8_t a, uint8_t b) {

}

Info Processor::getInfo() const {

}

/*
 * Returns true if register Vx == kk
 */
bool Processor::compareVxkk(uint16_t opcode) {
    auto regNo = (opcode & 0x0f00) >> 8;
    uint8_t byte = (opcode & 0x00ff);
    return (registers.at(regNo) == byte);
}

bool Processor::compareVxVy(uint16_t opcode) {
    auto reg1No = (opcode & 0x0f00) >> 8;
    auto reg2No = (opcode & 0x00f0) >> 8;
    return (registers.at(reg1No) == registers.at(reg2No));
}

template <typename T>
void Processor::setVxVy(int Vx, int Vy, T op) {
    registers.at(Vx) = op(registers.at(Vx), registers.at(Vy));
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
        case 0x5000 ... 0x5fff:
            if(opcode & 0x000f)
                InvalidCPUInstr(opcode);
            if(compareVxVy(opcode))
                PC += 2;
            break;
        /*
         * 6xkk - LD Vx, byte
         * Set Vx = kk
         */
        case 0x6000 ... 0x6fff: {
            auto Vxkk = getVxkk(opcode);
            registers.at(Vxkk.first) = Vxkk.second;
        } break;
        /*
         * 7xkk - ADD Vx, byte
         * Set Vx = Vx + kk
         */
        case 0x7000 ... 0x7fff: {
            auto Vxkk = getVxkk(opcode);
            registers.at(Vxkk.first) += Vxkk.second;
        } break;
        /*
         * 8xyN - N Vx, Vy
         * N is one of {1,...,7} U {e}
         */
        case 0x8000 ... 0x8fff: {
            int instruction = opcode & 0x000f;
            auto VxVy = getVxVy(opcode);
            auto Vx = VxVy.first;
            auto Vy = VxVy.second;
            switch(instruction) {
                /*
                 * 8xy0 - LD Vx, Vy
                 * Set Vx = Vy
                 */
                case 0:
                    registers.at(Vx) = registers.at(Vy);
                    break;
                /*
                 * 8xy1 - OR Vx, Vy
                 * Set Vx = Vx | Vy
                 */
                case 1:
                    setVxVy(Vx, Vy, std::bit_or<>());
                    break;
                /*
                 * 8xy2 - AND Vx, Vy
                 * Set Vx = Vx & Vy
                 */
                case 2:
                    setVxVy(Vx, Vy, std::bit_and<>());
                    break;
                /*
                 * 8xy3 - XOR Vx, Vy
                 * Set Vx = Vx XOR Vy
                 */
                case 3:
                    setVxVy(Vx, Vy, std::bit_xor<>());
                    break;
                /*
                 * 8xy4 - ADD Vx, Vy
                 * Set Vx = Vx + Vy, set VF = carry
                 */
                case 4: {
                    uint16_t result = registers.at(Vx) + registers.at(Vy);
                    registers.at(GPR_NO - 1) = (result > 255);
                    registers.at(Vx) = result & 0xff;
                } break;
                /*
                 * 8xy5 - SUB Vx, Vy
                 * Set Vx = Vx - Vy, set VF = NOT borrow
                 */
                case 5:
                    registers.at(GPR_NO - 1) = (registers.at(Vx) > registers.at(Vy));
                    registers.at(Vx) = registers.at(Vx) - registers.at(Vy);
                    break;
                /*
                 * 8xy6 - SHR Vx
                 * Set Vx = Vx >> 1
                 */
                case 6:

                default: InvalidCPUInstr(opcode);
            }

        } break;

        default: throw InvalidCPUInstruction("Unrecognized CPU instruction : " + std::to_string(opcode));
    }
}
