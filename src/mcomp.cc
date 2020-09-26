#include "mcomp.h"
#include <fstream>

Mcomp::Mcomp(): CPU{}, RAM{4} {}

void Mcomp::load(const std::string &path, unsigned int addr) {
    std::ifstream fin(path);
    char byte = 0;
    unsigned int ctr = addr;
    while(fin >> byte) RAM.setAddr(ctr++, byte);
    // return address = ctr
}

void Mcomp::run(const std::string &path, unsigned int addr) {
    load(path, addr);
    CPU.jump(addr);
}