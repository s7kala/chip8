#ifndef MEMORY_H
#define MEMORY_H

class Memory {
    public:
        // Initialize memory with size size_kb in kilobytes
        explicit Memory(unsigned int size_kb = 4);
        // Write value to MEM[addr]
        void setAddr(unsigned int addr, char value);
        /*
         * Write to mem with char* of size n
         * If n exceeds MEM size, the write is done for as long
         * as possible
         */
        void setAddrv(unsigned int addr, const char value[], int n);
        // Get value stored at MEM[addr]
        char getAddr(unsigned int addr) const;
        /*
         * Read values starting from addr into arv[] of length n
         * If n exceeds MEM size, the read is done for as long
         * as possible
         */
        char* getAddrv(unsigned int addr, char arv[], int n) const;
        // Get size of Memory
        unsigned int getSize() const;
        ~Memory();
    private:
        char* MEM;
        unsigned int size = 0;
};

#endif