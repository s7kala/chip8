#include "processor.h"
#include "ch8excepts.h"
#include "keypad.h"
#include "memory.h"
#include <sstream>
#ifdef DEBUG
#include "../asm/dasm.h"
#include <iostream>
#endif

/* ***************************** METHOD ABSTRACTIONS ********************************* */


/* ********** COMMON FUNCTIONS AND HELPERS ********** */

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

std::string hex2str(int num) {
    std::stringstream ss;
    ss << std::hex << num;
    return ss.str();
}

/*
 * Throw exception on invalid opcode
 */
void InvalidCPUInstr(uint16_t opcode) {
    std::string msg = "Unrecognized CPU instruction " + hex2str(opcode);
    throw InvalidCPUInstruction(msg.c_str());
}



/* ********************************* METHODS *************************************** */

Processor::Processor(Memory* pMem, Keypad* pkb): pMem{pMem}, pkb{pkb}, engine{dev()}, dist(0,255), clock{sf::Clock{}},
        src{sf::SoundBuffer{}}, beep{sf::Sound{}} {
    for(int i = 0; i < GPR_NO; ++i)
        registers.emplace_back(0);
    delay = sound = I = PC = 0;
    delayTimer = sf::seconds(0);
    soundTimer = sf::seconds(0);
    src.loadFromFile("../../audio/chip8-beep.wav");
    beep.setBuffer(src);
}

Processor::~Processor() noexcept = default;

void Processor::init(uint16_t retAddr) {
    if(!callStack.empty()) {
        throw ProcessorException("Processor already running\n");
    }
    callStack.push(retAddr);
}

void Processor::jump(uint16_t addr) {
    PC = addr;
}

bool Processor::run() {
    int state = true;
#ifdef DEBUG
    Disassembler dasm;
    std::cout << "Registers:\n";
    for(char i = 0; i < 16; ++i) {
        char reg = i + '0';
        if(i > 9) reg += 7;
        std::cout << "V" << reg << ": 0x" << std::hex << int(registers.at(int(i))) << '\n';
    }
    std::cout << "PC = 0x" << std::hex << int(PC) << '\n';
    std::cout << "I = 0x" << std::hex << int(I) << '\n';
    std::cout << "DT = 0x" << std::hex << int(delay) << '\n';
    std::cout << "ST = 0x" << std::hex << int(sound) << '\n';
    std::cout << "Stack top = 0x" << std::hex << int(callStack.top()) << '\n';
#endif
    static int instrNo = 0;
    if(!callStack.empty()) {
        uint16_t opcode = (pMem->getAddr(PC) << 8) + pMem->getAddr(PC + 1);
#ifdef DEBUG
        std::cout << "EXECUTING INSTRUCTION: ";
        dasm.decodeInstruction(opcode, std::cout, instrNo);
        std::cout << "Running a CPU cycle...\n";
#endif
        PC += 2;
        executeInstruction(opcode);
        if(delay > 0) {
            if(delayTimer == sf::seconds(0)) {
                delayTimer = clock.getElapsedTime();
            }
           if(clock.getElapsedTime() - delayTimer >= sf::milliseconds(1)) {
               --delay;
               delayTimer = clock.getElapsedTime();
           }
        } else if(delay == 0 && delayTimer != sf::seconds(0)) {
            delayTimer = sf::seconds(0);
        }
        if(sound > 0) {
            beep.play();
            if(soundTimer == sf::seconds(0)) {
                soundTimer = clock.getElapsedTime();
            }
            if(clock.getElapsedTime() - soundTimer >= sf::milliseconds(1)) {
                --sound;
                soundTimer = clock.getElapsedTime();
            }
        } else if(sound == 0 && soundTimer != sf::seconds(0)) {
            soundTimer = sf::seconds(0);
        }
        instrNo++;

    } else state = false;
    return state;
}

Info Processor::getInfo() const {
    return displayInstruction;
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
            displayInstruction = Info{};
            if(notifyObservers()) registers.at(GPR_NO - 1) = 1;
            else registers.at(GPR_NO - 1) = 0;
            break;
        /*
         * 00EE - RET
         * Return from a subroutine
         */
        case 0x00ee:
            PC = callStack.top();
            callStack.pop();
            break;
        /*
         * 1nnn - JP addr
         * Jump to location nnn
         */
        case 0x1000 ... 0x1fff:
            PC = opcode & 0x0fff;
            break;
        /*
         * 2nnn - CALL addr
         * Call subroutine at nnn
         */
        case 0x2000 ... 0x2fff:
            callStack.push(PC);
            PC = opcode & 0x0fff;
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
                    registers.at(GPR_NO - 1) = (registers.at(Vx) & 0x01);
                    registers.at(Vx) >>= 1;
                    break;
                /*
                 * 8xy7 - SUBN Vx, Vy
                 * Set Vx = Vy - Vx, set VF = NOT borrow
                 */
                case 7:
                    registers.at(GPR_NO - 1) = (registers.at(Vy) > registers.at(Vx));
                    registers.at(Vx) = registers.at(Vy) - registers.at(Vx);
                    break;
                /*
                 * 8xyE - SHL Vx
                 * Set Vx = Vx << 1
                 */
                case 14:
                    registers.at(GPR_NO - 1) = (registers.at(Vx) >> 7);
                    break;
                default: InvalidCPUInstr(opcode);
            }
        } break;
        /*
         * 9xy0 - SNE Vx, Vy
         * Skip next instruction if Vx != Vy
         */
        case 0x9000 ... 0x9fff: {
            if (opcode & 0x000f)
                InvalidCPUInstr(opcode);
            auto VxVy = getVxVy(opcode);
            if (registers.at(VxVy.first) != registers.at(VxVy.second))
                PC += 2;
        } break;
        /*
         * Annn - LD I, addr
         * Set I = nnn
         */
        case 0xa000 ... 0xafff:
            I = (opcode & 0x0fff);
            break;
        /*
         * Bnnn - JP V0, addr
         * Jump to location nnn + V0
         */
        case 0xb000 ... 0xbfff:
            PC = (opcode & 0x0fff) + registers.at(0);
            break;
        /*
         * Cxkk - RND Vx, byte
         * Set Vx = random byte & kk
         */
        case 0xc000 ... 0xcfff: {
            auto Vxkk = getVxkk(opcode);
            uint8_t rbyte = dist(engine);
            registers.at(Vxkk.first) = (rbyte & Vxkk.second);
        } break;
        /*
         * Dxyn - DRW Vx, Vy, nibble
         * Display n-byte sprite starting at memory location I at
         * (Vx, Vy), set VF = collision
         */
        case 0xd000 ... 0xdfff: {
            uint8_t n = (opcode & 0x000f);
            uint8_t sprite[n];
            pMem->getAddrv(I, sprite, n);
            displayInstruction.sprite.assign(sprite, sprite + n);
            auto VxVy = getVxVy(opcode);
            displayInstruction.Vx = registers.at(VxVy.first);
            displayInstruction.Vy = registers.at(VxVy.second);
            if(notifyObservers()) registers.at(GPR_NO - 1) = 1;
            else registers.at(GPR_NO - 1) = 0;
        } break;
        /*
         * Ex9E - SKP Vx
         * Skip next instruction if key with the value of Vx is pressed
         * ExA1 - SKNP Vx
         * Skip next instruction if key with the value of Vx is not pressed
         */
        case 0xe000 ... 0xefff: {
            auto Vxkk = getVxkk(opcode);
            uint8_t Vx = Vxkk.first;
            uint8_t skip = Vxkk.second;
            if(!pkb || !pkb->isConnected()) {
#ifdef DEBUG
                std::cout << "Keyboard not connected! Note: Keyboard is not supported with ASCII graphics!\n";
#endif
                break;
            }
            int key = registers.at(Vx);
            bool keyPressed = Keypad::isKeyPressed(registers.at(Vx));
#ifdef DEBUG
            if(keyPressed) std::cout << "Key " << int(registers.at(Vx)) << " was pressed!\n";
#endif
            if(skip == 0x9e) {
                if(keyPressed) PC += 2;
            } else if(skip == 0xa1) {
                if(!keyPressed) PC += 2;
            } else InvalidCPUInstr(opcode);
        } break;
        /*
         * FxPQ - PQ Vx
         * Do operation PQ on register Vx
         */
        case 0xf000 ... 0xffff: {
            auto Vxkk = getVxkk(opcode);
            uint8_t Vx = Vxkk.first;
            uint8_t subop = Vxkk.second;
            switch (subop) {
                /*
                 * Fx07 - LD Vx, DT
                 * Set Vx = delay timer value
                 */
                case 0x07:
                    registers.at(Vx) = delay;
                    break;
                /*
                 * Fx0A - LD Vx, K
                 * Wait for a key press, store the value of the key in Vx
                 */
                case 0x0a:
                    if(!pkb || !pkb->isConnected()) {
#ifdef DEBUG
                        std::cout << "Keyboard not connected! Note: Keyboard is not supported with ASCII graphics!\n";
#endif
                        break;
                    }
                    registers.at(Vx) = pkb->waitForKey();
                    break;
                /*
                 * Fx15 - LD DT, Vx
                 * Set delay timer = Vx
                 */
                case 0x15:
                    delay = registers.at(Vx);
                    break;
                /*
                 * Fx18 - LD ST, Vx
                 * Set sound timer = Vx
                 */
                case 0x18:
                    sound = registers.at(Vx);
                    break;
                /*
                 * Fx1E - ADD I, Vx
                 * Set I = I + Vx
                 */
                case 0x1e:
                    I += registers.at(Vx);
                    registers.at(GPR_NO - 1) = (I > 0xfff);
                    if(registers.at(GPR_NO -1)) I &= 0xfff;
                    break;
                /*
                 * Fx29 - LD F, Vx
                 * Set I = location of sprite for digit Vx
                 */
                case 0x29:
                    // sprites start at 0x50 in interpreter
                    I = 0x50 + int(registers.at(Vx)) * 5;
                    break;
                /*
                 * Fx33 - LD B, Vx
                 * Store BCD representation of Vx in memory locations
                 * I, I+1, I+2
                 */
                case 0x33: {
                    uint8_t value = registers.at(Vx);
                    pMem->setAddr(I, (value / 100) % 10);
                    pMem->setAddr(I + 1, (value / 10) % 10);
                    pMem->setAddr(I + 2, value % 10);
                } break;
                /*
                 * Fx55 - LD [I], Vx
                 * Store registers V0 through Vx in memory starting at location I
                 */
                case 0x55: {
                    for(int i = 0; i <= Vx; ++i) {
                        pMem->setAddr(I + i, registers.at(i));
                    }
                } break;
                /*
                 * Fx65 - LD Vx, [I]
                 * Read registers V0 through Vx from memory starting at location I
                 */
                case 0x65: {
                    for(int i = 0; i <= Vx; ++i) {
                        registers.at(i) = pMem->getAddr(I + i);
                    }
                } break;
                default: InvalidCPUInstr(opcode);
            }
        } break;
        default: InvalidCPUInstr(opcode);
    }
}
