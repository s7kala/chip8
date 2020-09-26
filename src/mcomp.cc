#include "mcomp.h"

Mcomp::Mcomp(): CPU{}, RAM{4} {}

void Mcomp::load(const std::string &path, unsigned int addr) {

}

void Mcomp::run(const std::string &path, unsigned int addr) {
    load(path, addr);
    CPU.jump(addr);
}