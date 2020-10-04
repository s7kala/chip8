#include "mcomp.h"
#include "memory.h"
#include "display.h"

#include <fstream>

Mcomp::Mcomp(): RAM{new Memory(4)}, CPU(RAM), screen{nullptr} {
    CPU.attach(screen);
}

void Mcomp::run(const std::string &path, uint16_t addr) {
    uint16_t retAddr = load(path, addr);
    CPU.jump(addr);
    CPU.run(retAddr);
}

uint16_t Mcomp::load(const std::string &path, uint16_t addr) {
    std::ifstream fin(path);
    char byte = 0;
    uint16_t ctr = addr;
    while(fin.get(byte)) RAM->setAddr(ctr++, byte);
    return ctr;
}

Mcomp::~Mcomp() {
    delete RAM;
}