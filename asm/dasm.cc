#include "dasm.h"
#include "excepts.h"
#include <fstream>
#include <sstream>

Disassembler::Disassembler(bool verbose): verbose{verbose} {}

std::string hex2str(int num) {
    std::stringstream ss;
    ss << std::hex << num;
    return ss.str();
}


void Disassembler::disassemble(const std::string& file, std::ostream& os) {
    std::ifstream fin(file);
    if(!bool(fin)) throw AsmException("File " + file + " does not exist", false);
    uint16_t opcode;
    int instrNo = 1;
    char high, low;
    while(fin.get(high)) {
        fin.get(low);
        opcode = (uint8_t(high) << 8) + uint8_t(low);
        if(opcode == 0) break;
        decodeInstruction(opcode, os, instrNo - 1);
        ++instrNo;
    }
}

void InvalidCPUInstr(uint16_t opcode) {
    throw AsmException("Invalid CPU Instruction: " + hex2str(opcode), false);
}

void Disassembler::decodeInstruction(uint16_t opcode, std::ostream& os, int instrNo) {
    std::string b0(hex2str(opcode & 0x000f));
    std::string b1(hex2str((opcode & 0x00f0) >> 4));
    std::string b2(hex2str((opcode & 0x0f00) >> 8));
    std::string b3(hex2str((opcode & 0xf000) >> 12));
    if(instrNo % 4 == 0) {
        os << "0x" << 200 + instrNo*2 << ": ";
    }
    os << "\t";
    switch (opcode) {
        /*
         * 00E0 - CLS
         * Clear the display
         */
        case 0x00e0:
            os << "CLS\t\t\t";
            break;
        /*
         * 00EE - RET
         * Return from a subroutine
         */
        case 0x00ee:
            os << "RET\t\t\t";
            break;
        /*
         * 1nnn - JP addr
         * Jump to location nnn
         */
        case 0x1000 ... 0x1fff:
            os << "JP\t#" << b2 << b1 << b0 << "\t\t";
            break;
        /*
         * 2nnn - CALL addr
         * Call subroutine at nnn
         */
        case 0x2000 ... 0x2fff:
            os << "CALL\t#" << b2 << b1 << b0 << "\t\t";
            break;
        /*
         * 3xkk - SE Vx, byte
         * Skip next instruction if Vx = kk
         */
        case 0x3000 ... 0x3fff:
            os << "SE\tV" << b2 << ",\t#" << b1 << b0 << "\t";
            break;
        /*
         * 4xkk - SNE Vx, byte
         * Skip next instruction if Vx != kk
         */
        case 0x4000 ... 0x4fff:
            os << "SNE\tV" << b2 << ",\t#" << b1 << b0 << "\t";
            break;
        /*
         * 5xy0 - SE Vx, Vy
         * Skip next instruction if Vx = Vy
         */
        case 0x5000 ... 0x5fff:
            if(opcode & 0x000f)
                InvalidCPUInstr(opcode);
            os << "SE\tV" << b2 << ",\tV" << b1 << "\t";
            break;
        /*
         * 6xkk - LD Vx, byte
         * Set Vx = kk
         */
        case 0x6000 ... 0x6fff:
            os << "LD\tV" << b2 << ",\t#" << b1 << b0 << "\t";
            break;
        /*
         * 7xkk - ADD Vx, byte
         * Set Vx = Vx + kk
         */
        case 0x7000 ... 0x7fff:
            os << "ADD\tV" << b2 << ",\t#" << b1 << b0 << "\t";
            break;
        /*
         * 8xyN - N Vx, Vy
         * N is one of {1,...,7} U {e}
         */
        case 0x8000 ... 0x8fff: {
            int instruction = opcode & 0x000f;
            switch(instruction) {
                /*
                 * 8xy0 - LD Vx, Vy
                 * Set Vx = Vy
                 */
                case 0:
                    os << "LD\tV" << b2 << ",\tV" << b1 << '\t';
                    break;
                /*
                 * 8xy1 - OR Vx, Vy
                 * Set Vx = Vx | Vy
                 */
                case 1:
                    os << "OR\tV" << b2 << ",\tV" << b1 << '\t'; 
                    break;
                /*
                 * 8xy2 - AND Vx, Vy
                 * Set Vx = Vx & Vy
                 */
                case 2:
                    os << "AND\tV" << b2 << ",\tV" << b1 << '\t';
                    break;
                /*
                 * 8xy3 - XOR Vx, Vy
                 * Set Vx = Vx XOR Vy
                 */
                case 3:
                    os << "XOR\tV" << b2 << ",\tV" << b1 << '\t';
                    break;
                /*
                 * 8xy4 - ADD Vx, Vy
                 * Set Vx = Vx + Vy, set VF = carry
                 */
                case 4:
                    os << "ADD\tV" << b2 << ",\tV" << b1 << '\t';
                    break;
                /*
                 * 8xy5 - SUB Vx, Vy
                 * Set Vx = Vx - Vy, set VF = NOT borrow
                 */
                case 5:
                    os << "SUB\tV" << b2 << ",\tV" << b1 << '\t';
                    break;
                /*
                 * 8xy6 - SHR Vx
                 * Set Vx = Vx >> 1
                 */
                case 6:
                    os << "SHR\tV" << b2 << "\t\t";
                    break;
                /*
                 * 8xy7 - SUBN Vx, Vy
                 * Set Vx = Vy - Vx, set VF = NOT borrow
                 */
                case 7:
                    os << "SUBN\tV" << b2 << ",\tV" << b1 << '\t';
                    break;
                /*
                 * 8xyE - SHL Vx
                 * Set Vx = Vx << 1
                 */
                case 14:
                    os << "SHL\tV" << b2 << "\t\t";
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
            os << "SNE\tV" << b2 << ",\tV" << b1 << '\t';
        } break;
        /*
         * Annn - LD I, addr
         * Set I = nnn
         */
        case 0xa000 ... 0xafff:
            os << "LD\tI,\t#" << b2 << b1 << b0 << "\t";
            break;
        /*
         * Bnnn - JP V0, addr
         * Jump to location nnn + V0
         */
        case 0xb000 ... 0xbfff:
            os << "JP\tV0,\t" << b2 << b1 << b0 << '\t';
            break;
        /*
         * Cxkk - RND Vx, byte
         * Set Vx = random byte & kk
         */
        case 0xc000 ... 0xcfff:
            os << "RND\tV" << b2 << ",\t" << b1 << b0 << '\t';
            break;
        /*
         * Dxyn - DRW Vx, Vy, nibble
         * Display n-byte sprite starting at memory location I at
         * (Vx, Vy), set VF = collision
         */
        case 0xd000 ... 0xdfff:
            os << "DRW\tV" << b2 << ",\tV" << b1 << ",\t#" << b0;
            break;
        /*
         * Ex9E - SKP Vx
         * Skip next instruction if key with the value of Vx is pressed
         * ExA1 - SKNP Vx
         * Skip next instruction if key with the value of Vx is not pressed
         */
        case 0xe000 ... 0xefff: {
            uint8_t skip = opcode & 0x00ff;
            if(skip == 0x9e) {
                os << "SKP";
            } else if(skip == 0xa1) {
                os << "SKNP";
            } else InvalidCPUInstr(opcode);
            os << "\tV" << b2 << "\t\t";
        } break;
        /*
         * FxPQ - PQ Vx
         * Do operation PQ on register Vx
         */
        case 0xf000 ... 0xffff: {
            uint8_t subop = opcode & 0x00ff;
            switch (subop) {
                /*
                 * Fx07 - LD Vx, DT
                 * Set Vx = delay timer value
                 */
                case 0x07:
                    os << "LD\tV" << b2 << ",\t" << "DT" << '\t';
                    break;
                /*
                 * Fx0A - LD Vx, K
                 * Wait for a key press, store the value of the key in Vx
                 */
                case 0x0a:
                    os << "LD\tV" << b2 << ",\t" << "K" << '\t';
                    // Add keyboard stuff here
                    break;
                /*
                 * Fx15 - LD DT, Vx
                 * Set delay timer = Vx
                 */
                case 0x15:
                    os << "LD\tDT,\tV" << b2 << "\t";
                    break;
                /*
                 * Fx18 - LD ST, Vx
                 * Set sound timer = Vx
                 */
                case 0x18:
                    os << "LD\tST,\tV" << b2 << "\t";
                    break;
                /*
                 * Fx1E - ADD I, Vx
                 * Set I = I + Vx
                 */
                case 0x1e:
                    os << "ADD\tI,\tV" << b2 << "\t";
                    break;
                /*
                 * Fx29 - LD F, Vx
                 * Set I = location of sprite for digit Vx
                 */
                case 0x29:
                    os << "LD\tF,\tV" << b2 << "\t";
                    break;
                /*
                 * Fx33 - LD B, Vx
                 * Store BCD representation of Vx in memory locations
                 * I, I+1, I+2
                 */
                case 0x33:
                    os << "LD\tB,\tV" << b2 << "\t";
                    break;
                /*
                 * Fx55 - LD [I], Vx
                 * Store registers V0 through Vx in memory starting at location I
                 */
                case 0x55:
                    os << "LD\t[I],\tV" << b2 << "\t";
                    break;
                /*
                 * Fx65 - LD Vx, [I]
                 * Read registers V0 through Vx from memory starting at location I
                 */
                case 0x65:
                    os << "LD\tV" << b2 << ",\t" << "[I]" << '\t';
                    break;
                default: InvalidCPUInstr(opcode);
            }
        } break;
        default: InvalidCPUInstr(opcode);
    }
    os << "\t; " << b3 << b2 << b1 << b0 << '\n';
}