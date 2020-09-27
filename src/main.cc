#include "mcomp.h"
#include <iostream>
#include <vector>

void use(const char* progname) {
    std::cout << progname << " " << "[options] [filename]\n";
    std::cout << "\"" << progname << " --help\" for help\n";
}

void help() {

}

int main(int argc, char** argv) {
    int rc = 0;
    if(argc < 2) {
        use(argv[0]);
        rc = 1;
    } else {
        std::string file = argv[argc - 1];
        // evaluate options here
        // ------
        for(int i = 1; i < argc - 1; ++i) {
            std::string option(argv[i]);
            if(option == "-e" || option == "--ETI660") {

            } else if(option == "-g" || option == "--graphics") {

            } else if(option == "-v" || option == "--verbose") {

            } else if (option == "-h" || option == "--help") {

            } else {
                    std::cout << "Unrecognized command-line option: " << option << std::endl;

            }
        }
        // TO-DO impl options
        try {
            Mcomp emulator;
            emulator.run(file);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return rc;
}