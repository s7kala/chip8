#include "mcomp.h"
#include "memory.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "keyboard.h"

#include <fstream>
#include <stdexcept>
#include <chrono>
#include <thread>


Mcomp::Mcomp(bool graphics): RAM{new Memory(4)}, kb{new Keyboard}, CPU(RAM, kb), graphics{graphics} {
    if(graphics) {
        auto disp = new GraphicsDisplay;
        kb->attach(&disp->window);
        screen = disp;
    }
    else screen = new TextDisplay;
    CPU.attach(screen);
    // add sprites in interpreter memory (0x000 to 0x1ff)
    //
    uint8_t fonts[] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    RAM->setAddrv(0x50, fonts, 80);
}

void Mcomp::run(const std::string &path, uint16_t addr) {
    boot(path, addr);
    while(CPU.run()) {
        // temp fix for text display
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}

bool Mcomp::emulate(const std::string &path, uint16_t addr) {
    return CPU.run();
}

void Mcomp::boot(const std::string &path, uint16_t addr) {
#ifdef DEBUG
    std::cout << "Booting program " << path << " into memory at 0x" << std::hex << addr << '\n';
#endif
    uint16_t retAddr = load(path, addr);
#ifdef DEBUG
    std::cout << "Return address is 0x" << std::hex << int(retAddr) << '\n';
#endif
    CPU.init(retAddr);
    CPU.jump(addr);
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
    delete screen;
    delete kb;
}
