#include "mcomp.h"
#include <iostream>

void use(const char* progname) {
    std::cout << progname << " " << "[options] [filename]\n";
}   

int main(int argc, char** argv) {
    int rc = 0;
    if(argc < 2) {
        use(argv[0]);
        rc = 1;
    } else {
        std::string file = argv[argc - 1];
        // evaluate options here
        //
        try {
            Mcomp emulator;
            emulator.load(file);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return rc;
}