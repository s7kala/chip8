#include "processor.h"

Processor::Processor() {
    for(int i = 0; i < GPR_NO; ++i) {
        registers.emplace_back(Register(std::to_string(i)));
    }
    delay = Register("D");
    sound = Register("S");
    I[0] = Register("IL");
    I[1] = Register("IH");
    PC[0] = Register("PCL");
    PC[1] = Register("PCH");
}

void Processor::jump(unsigned int addr) {

}