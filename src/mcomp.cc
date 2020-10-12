#include "mcomp.h"
#include "memory.h"
#include "textdisplay.h"

#include <fstream>
#include <stdexcept>
#include <chrono>
#include <thread>

Mcomp::Mcomp(): RAM{new Memory(4)}, CPU(RAM), screen{new TextDisplay} {
    CPU.attach(screen);
    // add sprites in interpreter memory (0x000 to 0x1ff)
    //
}

void Mcomp::run(const std::string &path, uint16_t addr) {
    uint16_t retAddr = load(path, addr);
    CPU.init(retAddr);
    CPU.jump(addr);
    while(CPU.run()) {
        // temp fix for text display
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
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
