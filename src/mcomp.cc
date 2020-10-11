#include "mcomp.h"
#include "memory.h"
#include "display.h"
#include "textdisplay.h"

#include <fstream>
#include <stdexcept>

Mcomp::Mcomp(): RAM{new Memory(4)}, CPU(RAM), screen{new TextDisplay} {
    CPU.attach(screen);
}

void Mcomp::run(const std::string &path, uint16_t addr) {
    uint16_t retAddr = load(path, addr);
    CPU.init(retAddr);
    CPU.jump(addr);
    while(CPU.run())
        screen->view();
}

uint16_t Mcomp::load(const std::string &path, uint16_t addr) {
    std::ifstream fin(path);
    if(!bool(fin)) {
        throw std::runtime_error("File " + path + " does not exist");
    }
    char byte = 0;
    uint16_t ctr = addr;
    while(fin.get(byte)) RAM->setAddr(ctr++, byte);
    return ctr;
}

Mcomp::~Mcomp() {
    delete RAM;
}
