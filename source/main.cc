//#include "mcomp.h"
#include <iostream>

void use(const char* progname) {
    std::cout << progname << " " << "[options] [filename]\n";
}   

int main(int argc, char** argv) {
   // Mcomp vm;
    int rc = 0;
    if(argc < 2) {
        use(argv[0]);
        rc = 1;
    } else {

    }
    return rc;
}