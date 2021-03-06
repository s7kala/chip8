#include "memory.h"
#include <cstring>
#include <stdexcept>
#include <string>

Memory::Memory(unsigned int size_kb) {
    MEM = new uint8_t [size_kb * 1024];
    size = 1024 * size_kb;
    std::memset(MEM, 0, size);
}

void rangeCheck(unsigned int addr, unsigned int size) {
    if(addr < 0 || addr >= size)
        throw std::out_of_range("ERROR: Address out of range: " + std::to_string(addr));
}

void Memory::setAddr(unsigned int addr, uint8_t value) {
    rangeCheck(addr, size);
    MEM[addr] = value;
}

void Memory::setAddrv(unsigned int addr, const uint8_t value[], int n) {
    rangeCheck(addr, size);
    for(int i = 0; i < n && addr + i < size; ++i) {
        MEM[addr + i] = value[i];
    }
}

uint8_t Memory::getAddr(unsigned int addr) const {
    rangeCheck(addr, size);
    return MEM[addr];
}

uint8_t* Memory::getAddrv(unsigned int addr, uint8_t* arv, int n) const {
    rangeCheck(addr, size);
    for(int i = 0; i < n && addr + i < size; ++i) {
        arv[i] = MEM[addr + i];
    }
    return arv;
}

unsigned int Memory::getSize() const {
    return size;
}

Memory::~Memory() {
    delete [] MEM;
}
