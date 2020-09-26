#include "processor.h"

void Processor::jump(unsigned int addr) {
    PC = addr;
}