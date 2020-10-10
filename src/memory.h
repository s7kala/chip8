#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
    public:
        // Initialize memory with size size_kb in kilobytes
        explicit Memory(unsigned int size_kb = 4);
        // Write value to MEM[addr]
        void setAddr(unsigned int addr, uint8_t value);
        /*
         * Write to mem with uint8_t* of size n
         * If n exceeds MEM size, the write is done for as long
         * as possible
         */
        void setAddrv(unsigned int addr, const uint8_t value[], int n);
        // Get value stored at MEM[addr]
        uint8_t getAddr(unsigned int addr) const;
        /*
         * Read values starting from addr into arv[] of length n
         * If n exceeds MEM size, the read is done for as long
         * as possible
         */
        uint8_t * getAddrv(unsigned int addr, uint8_t arv[], int n) const;
        // Get size of Memory
        unsigned int getSize() const;
        ~Memory();
    private:
        uint8_t* MEM = nullptr;
        unsigned int size = 0;
};

#endif
